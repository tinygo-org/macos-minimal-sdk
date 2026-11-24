#!/usr/bin/env python3

# This file is placed in the public domain.

# This file converts a simple header file like this:
#
#    #include <stdio.h>
#    #include <stdlib.h>
#
# to an assembly file that defines stub functions:
#
#    .global _malloc
#    _malloc:
#
#    .global _printf
#    _printf:
#
# ...etc.

import argparse
import sys
from collections import OrderedDict

# If this fails, install the Clang python bindings.
# For example, on Debian that's something like:
#    apt-get install python3-clang-13
import clang.cindex

# For some information on the (sparsely documented) clang package for Python:
# https://eli.thegreenplace.net/2011/07/03/parsing-c-in-python-with-clang

def generateStubs(sysroot, outfile, target):
    # These symbols are not defined in the header files, but must be declared
    # anyway.
    symbols = {
        'dyld_stub_binder',
        '___bzero',
        '__tlv_bootstrap',
        '___memcpy_chk', '___memmove_chk', '___memset_chk',
        '___stack_chk_guard', '___stack_chk_fail',
        # Exported by libSystem, but declared in headers that are not part of
        # this minimal SDK:
        '_ioctl',           # <sys/ioctl.h>
        '__NSGetExecutablePath',  # <mach-o/dyld.h>
        '_dladdr',          # <dlfcn.h>
        # <mach/mach.h>
        '_mach_task_self_', '_mach_thread_self', '_mach_port_deallocate', '_vm_deallocate',
        '_task_threads', '_thread_suspend', '_thread_resume', '_thread_get_state', '_thread_info',
        '___sincos_stret', '___sincosf_stret'  # newer <math.h>; called by LLVM-generated code
    }

    # Builtins called by LLVM-generated code, exported by libSystem from libcompiler_rt.
    # Taken from usr/lib/system/libcompiler_rt.tbd in the macOS SDK.
    symbols |= {
        '___atomic_compare_exchange', '___atomic_compare_exchange_1',
        '___atomic_compare_exchange_2', '___atomic_compare_exchange_4',
        '___atomic_compare_exchange_8', '___atomic_exchange', '___atomic_exchange_1',
        '___atomic_exchange_2', '___atomic_exchange_4', '___atomic_exchange_8',
        '___atomic_fetch_add_1', '___atomic_fetch_add_2', '___atomic_fetch_add_4',
        '___atomic_fetch_add_8', '___atomic_fetch_and_1', '___atomic_fetch_and_2',
        '___atomic_fetch_and_4', '___atomic_fetch_and_8', '___atomic_fetch_or_1',
        '___atomic_fetch_or_2', '___atomic_fetch_or_4', '___atomic_fetch_or_8',
        '___atomic_fetch_sub_1', '___atomic_fetch_sub_2', '___atomic_fetch_sub_4',
        '___atomic_fetch_sub_8', '___atomic_fetch_xor_1', '___atomic_fetch_xor_2',
        '___atomic_fetch_xor_4', '___atomic_fetch_xor_8', '___atomic_is_lock_free',
        '___atomic_load', '___atomic_load_1', '___atomic_load_2', '___atomic_load_4',
        '___atomic_load_8', '___atomic_store', '___atomic_store_1', '___atomic_store_2',
        '___atomic_store_4', '___atomic_store_8', '___chkstk_darwin', '___clear_cache',
        '___clzti2', '___divti3', '___enable_execute_stack', '___extendhfsf2',
        '___fixdfti', '___fixsfti', '___fixunsdfti', '___fixunssfti', '___floattidf',
        '___floattisf', '___floatuntidf', '___floatuntisf', '___gcc_personality_v0',
        '___gnu_f2h_ieee', '___gnu_h2f_ieee', '___modti3', '___muldc3', '___mulsc3',
        '___powidf2', '___powisf2', '___truncdfhf2', '___truncsfhf2', '___udivmodti4',
        '___udivti3', '___umodti3', '_atomic_flag_clear', '_atomic_flag_clear_explicit',
        '_atomic_flag_test_and_set', '_atomic_flag_test_and_set_explicit',
        '_atomic_signal_fence', '_atomic_thread_fence'
    }
    if target.startswith('x86_64'):
        symbols |= {
            '___absvdi2', '___absvsi2', '___absvti2', '___addvdi3', '___addvsi3',
            '___addvti3', '___ashldi3', '___ashlti3', '___ashrdi3', '___ashrti3',
            '___clzdi2', '___clzsi2', '___cmpdi2', '___cmpti2', '___ctzdi2',
            '___ctzsi2', '___ctzti2', '___divdc3', '___divdi3', '___divsc3',
            '___divxc3', '___ffsdi2', '___ffsti2', '___fixdfdi', '___fixsfdi',
            '___fixunsdfdi', '___fixunsdfsi', '___fixunssfdi', '___fixunssfsi',
            '___fixunsxfdi', '___fixunsxfsi', '___fixunsxfti', '___fixxfdi',
            '___fixxfti', '___floatdidf', '___floatdisf', '___floatdixf',
            '___floattixf', '___floatundidf', '___floatundisf', '___floatundixf',
            '___floatuntixf', '___lshrdi3', '___lshrti3', '___moddi3', '___muldi3',
            '___mulodi4', '___mulosi4', '___muloti4', '___multi3', '___mulvdi3',
            '___mulvsi3', '___mulvti3', '___mulxc3', '___negdi2', '___negti2',
            '___negvdi2', '___negvsi2', '___negvti2', '___paritydi2', '___paritysi2',
            '___parityti2', '___popcountdi2', '___popcountsi2', '___popcountti2',
            '___powixf2', '___subvdi3', '___subvsi3', '___subvti3', '___ucmpdi2',
            '___ucmpti2', '___udivdi3', '___udivmoddi4', '___umoddi3'
        }

    # Parse the src/libSystem.h file to get a list of functions declared in libSystem.
    index = clang.cindex.Index.create()
    args = args=['--sysroot='+sysroot, '-Werror', '--target='+target]
    tu = index.parse('src/libSystem.h', args=args)
    if len(tu.diagnostics):
        print('failed to extract function stubs using %s:' % args)
        for diag in tu.diagnostics:
            print(diag)
        sys.exit(1)
    for child in tu.cursor.get_children():
        if child.kind != clang.cindex.CursorKind.FUNCTION_DECL and child.kind != clang.cindex.CursorKind.VAR_DECL:
            continue
        if child.linkage != clang.cindex.LinkageKind.EXTERNAL:
            continue
        symbols.add(child.mangled_name)

    # Now write a stub assembly file that defines these files as stubs. They
    # can't be called, they're only provided to let the linker know that these
    # symbols live in libSystem.B.dylib.
    f = open(outfile, 'w')
    f.write('// GENERATED FILE - DO NOT EDIT\n')
    f.write('// This file was generated using generate-stubs.py with --target=%s\n' % target)
    for symbol in sorted(list(symbols)):
        f.write('\n.global %s\n%s:\n' % (symbol, symbol))
    f.close()


def main():
    parser = argparse.ArgumentParser(description='Create libSystem.s stubs')
    parser.add_argument('--target', type=str, default='x86_64-apple-macosx10.12.0', help='Clang --target flag')
    parser.add_argument('sysroot', type=str, help='path to sysroot directory')
    parser.add_argument('output', type=str, help='where to write assembly stubs')
    args = parser.parse_args()
    generateStubs(args.sysroot, args.output, args.target)

if __name__ == '__main__':
    main()
