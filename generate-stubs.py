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
    symbols = {'dyld_stub_binder', '___bzero'}

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
