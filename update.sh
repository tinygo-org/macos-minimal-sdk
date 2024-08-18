#!/bin/sh

# This file is placed in the public domain.

# Exit early when this script encounters an error.
set -e

# Load version variables.
. ./versions.inc

# Prepare some utility variables, used below.
Libc="Libc-$Libc_version"
xnu="xnu-$xnu_version"
AvailabilityVersions="AvailabilityVersions-$AvailabilityVersions_version"
libmalloc="libmalloc-$libmalloc_version"
libplatform="libplatform-$libplatform_version"
libpthread="libpthread-$libpthread_version"
CarbonHeaders="CarbonHeaders-$CarbonHeaders_version"
Libm="Libm-$Libm_version"
sysroot=src
include="$sysroot/usr/include"

# Download libraries (if needed).
wget -P download --no-clobber --no-verbose \
	"https://opensource.apple.com/tarballs/AvailabilityVersions/$AvailabilityVersions.tar.gz" \
	"https://opensource.apple.com/tarballs/CarbonHeaders/$CarbonHeaders.tar.gz" \
	"https://opensource.apple.com/tarballs/Libc/$Libc.tar.gz" \
	"https://opensource.apple.com/tarballs/Libm/$Libm.tar.gz" \
	"https://opensource.apple.com/tarballs/libmalloc/$libmalloc.tar.gz" \
	"https://opensource.apple.com/tarballs/libplatform/$libplatform.tar.gz" \
	"https://opensource.apple.com/tarballs/libpthread/$libpthread.tar.gz" \
	"https://opensource.apple.com/tarballs/xnu/$xnu.tar.gz"

# Extract source files.
# Order matters: some files are duplicated in different tarballs.
rm -rf $include
mkdir -p $include/sys
mkdir -p $sysroot/usr/local/libexec
tar -C $sysroot/usr/local/libexec --strip-components=1 -xf "download/$AvailabilityVersions.tar.gz" \
        "AvailabilityVersions-$AvailabilityVersions/availability.pl"
tar -C $include           --strip-components=1 -xf "download/$CarbonHeaders.tar.gz" \
        "CarbonHeaders-$CarbonHeaders/TargetConditionals.h"
tar -C $include           --strip-components=2 -xf "download/$Libc.tar.gz" \
        "Libc-$Libc/include"
tar -C $include           --strip-components=3 -xf "download/$Libm.tar.gz" \
        "Libm-$Libm/Source/Intel/math.h"
tar -C $include           --strip-components=2 -xf "download/$libmalloc.tar.gz" \
        "libmalloc-$libmalloc/include/malloc"
tar -C $include           --strip-components=2 -xf "download/$libplatform.tar.gz" \
        "libplatform-$libplatform/include/ucontext.h"
tar -C $include/sys       --strip-components=3 -xf "download/$libpthread.tar.gz" \
        "libpthread-$libpthread/include/sys/_pthread"
tar -C $include           --strip-components=3 -xf "download/$xnu.tar.gz" \
        "xnu-$xnu/libsyscall/wrappers/gethostuuid.h"
tar -C $include           --strip-components=2 -xf "download/$xnu.tar.gz" \
        "xnu-$xnu/bsd/arm/endian.h" \
        "xnu-$xnu/bsd/arm/limits.h" \
        "xnu-$xnu/bsd/arm/_limits.h" \
        "xnu-$xnu/bsd/arm/_mcontext.h" \
        "xnu-$xnu/bsd/arm/param.h" \
        "xnu-$xnu/bsd/arm/_param.h" \
        "xnu-$xnu/bsd/arm/types.h" \
        "xnu-$xnu/bsd/bsm/audit.h" \
        "xnu-$xnu/bsd/i386/endian.h" \
        "xnu-$xnu/bsd/i386/limits.h" \
        "xnu-$xnu/bsd/i386/_limits.h" \
        "xnu-$xnu/bsd/i386/_mcontext.h" \
        "xnu-$xnu/bsd/i386/param.h" \
        "xnu-$xnu/bsd/i386/_param.h" \
        "xnu-$xnu/bsd/i386/types.h" \
        "xnu-$xnu/bsd/machine/endian.h" \
        "xnu-$xnu/bsd/machine/limits.h" \
        "xnu-$xnu/bsd/machine/_mcontext.h" \
        "xnu-$xnu/bsd/machine/param.h" \
        "xnu-$xnu/bsd/machine/types.h" \
        "xnu-$xnu/bsd/sys/appleapiopts.h" \
        "xnu-$xnu/bsd/sys/cdefs.h" \
        "xnu-$xnu/bsd/sys/dirent.h" \
        "xnu-$xnu/bsd/sys/_endian.h" \
        "xnu-$xnu/bsd/sys/errno.h" \
        "xnu-$xnu/bsd/sys/event.h" \
        "xnu-$xnu/bsd/sys/fcntl.h" \
        "xnu-$xnu/bsd/sys/lock.h" \
        "xnu-$xnu/bsd/sys/make_symbol_aliasing.sh" \
        "xnu-$xnu/bsd/sys/make_posix_availability.sh" \
        "xnu-$xnu/bsd/sys/mman.h" \
        "xnu-$xnu/bsd/sys/param.h" \
        "xnu-$xnu/bsd/sys/proc.h" \
        "xnu-$xnu/bsd/sys/queue.h" \
        "xnu-$xnu/bsd/sys/resource.h" \
        "xnu-$xnu/bsd/sys/signal.h" \
        "xnu-$xnu/bsd/sys/select.h" \
        "xnu-$xnu/bsd/sys/_select.h" \
        "xnu-$xnu/bsd/sys/stat.h" \
        "xnu-$xnu/bsd/sys/stdio.h" \
        "xnu-$xnu/bsd/sys/sysctl.h" \
        "xnu-$xnu/bsd/sys/syslimits.h" \
        "xnu-$xnu/bsd/sys/time.h" \
        "xnu-$xnu/bsd/sys/_types" \
        "xnu-$xnu/bsd/sys/types.h" \
        "xnu-$xnu/bsd/sys/_types.h" \
        "xnu-$xnu/bsd/sys/ucontext.h" \
        "xnu-$xnu/bsd/sys/ucred.h" \
        "xnu-$xnu/bsd/sys/unistd.h" \
        "xnu-$xnu/bsd/sys/vm.h" \
        "xnu-$xnu/bsd/sys/wait.h" \
        "xnu-$xnu/EXTERNAL_HEADERS/Availability.h" \
        "xnu-$xnu/EXTERNAL_HEADERS/AvailabilityInternal.h" \
        "xnu-$xnu/libkern/libkern/_OSByteOrder.h" \
        "xnu-$xnu/libkern/libkern/arm/OSByteOrder.h" \
        "xnu-$xnu/libkern/libkern/i386/_OSByteOrder.h" \
        "xnu-$xnu/osfmk/arm/arch.h" \
        "xnu-$xnu/osfmk/mach/arm/boolean.h" \
        "xnu-$xnu/osfmk/mach/arm/_structs.h" \
        "xnu-$xnu/osfmk/mach/arm/vm_types.h" \
        "xnu-$xnu/osfmk/mach/i386/boolean.h" \
        "xnu-$xnu/osfmk/mach/i386/_structs.h" \
        "xnu-$xnu/osfmk/mach/i386/vm_types.h" \
        "xnu-$xnu/osfmk/mach/machine/boolean.h" \
        "xnu-$xnu/osfmk/mach/machine/_structs.h" \
        "xnu-$xnu/osfmk/mach/machine/vm_types.h" \
        "xnu-$xnu/osfmk/mach/boolean.h" \
        "xnu-$xnu/osfmk/mach/port.h"

# Generate some files.
$include/sys/make_symbol_aliasing.sh $sysroot $include/sys/_symbol_aliasing.h
bash $include/sys/make_posix_availability.sh $include/sys/_posix_availability.h

# Remove everything that's not a header file.
find $include -type f -not -name '*.h' -delete
rm $sysroot/usr/local/libexec/availability.pl
rm -r $include/FreeBSD $include/NetBSD
find $sysroot -type d -empty -delete

# Remove some files not included in /usr/include.
rm $include/asm.h
rm $include/authentication.h
rm $include/sys/_types/_user*
rm $include/kvm.h


# Replace stdint.h with a different version, because stdint.h doesn't have an
# open source license.
cp -p src/stdint.h $include/stdint.h

# Replace these files with an empty file because they don't have an open source
# license. So far, this seems to work well enough.
printf "" > $include/libkern/arm/OSByteOrder.h
printf "" > $include/arm/_limits.h
printf "" > $include/arm/_param.h

# Replace src/signal.h. This avoids including arm/signal.h, which doesn't have
# an open source license.
cp -p src/signal.h $include/machine/signal.h

# Replace machine/_types.h, arm/_types.h, and i386/_types.h with a single file.
# Do forward includes though, because arm/types.h and i386/types.h still
# include the */_types.h version.
echo "#include <machine/_types.h>" > $include/arm/_types.h
echo "#include <machine/_types.h>" > $include/i386/_types.h
cp -p src/_types.h $include/machine/_types.h


# Some header files have a pattern like this:
#   //Begin-Libc
#   (some code)
#   //End-Libc
# It appears that this is some sort of #if guard and should be stripped away.
find $include -type f -name '*.h' -print0 | xargs -0 perl -p0i -e 's%//Begin-Libc\n.*?//End-Libc\n%%gms'

# Some files need to be patched to work.
# Because we aren't targeting iPhones, we can set them all to 0.
perl -pi -e 's/\@CONFIG_(EMBEDDED|IPHONE|IPHONE_SIMULATOR)\@ +/0/g' $include/TargetConditionals.h

# Remove PLATFORM_MacOSX ifdef guards. We're always on MacOSX.
perl -pi -e 's%^(#ifdef PLATFORM_MacOSX|#endif /\* PLATFORM_MacOSX \*/)\n%%g' $include/sys/cdefs.h

# Now generate the assembly stubs for libSystem.B.dylib.
rm -f $sysroot/x86_64/libSystem.s $sysroot/arm64/libSystem.s
mkdir -p $sysroot/x86_64 $sysroot/arm64
./generate-stubs.py --target=x86_64-apple-macos10.12 $sysroot $sysroot/x86_64/libSystem.s
./generate-stubs.py --target=arm64-apple-macos11     $sysroot $sysroot/arm64/libSystem.s
