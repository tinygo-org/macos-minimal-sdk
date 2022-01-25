# Minimal SDK for macOS

[![CI results](https://github.com/aykevl/macos-minimal-sdk/actions/workflows/test.yml/badge.svg)](https://github.com/aykevl/macos-minimal-sdk/actions/workflows/test.yml)

This repository provides the basis to build a cross compiler for macOS. With it, you can compile small command line tools from any operating system to macOS.

Features:

  * Cross compile from any OS to macOS using Clang/LLVM.
  * Open license. All header files have been obtained from [opensource.apple.com](https://opensource.apple.com/) and are licensed under the [Apple Public Source License 2.0](https://opensource.apple.com/license/apsl/). Therefore, this SDK is also open source.

## Example

Say you have a hello world C file, named `hello.c`:

```c
#include <stdio.h>

int main(void) {
    printf("Hello world!\n");
    return 0;
}
```

You can then build it on any host with Clang 13+ installed like this (using `clang-13` here as an example):

```
$ clang-13 --target=x86_64-apple-macos10.12 --sysroot=sysroot-macos-x86_64 -fuse-ld=lld -o hello hello.c
$ file hello
hello: Mach-O 64-bit x86_64 executable, flags:<NOUNDEFS|DYLDLINK|TWOLEVEL|PIE>
```

It can also compile to ARM64 (aka "Apple Silicon"):

```
$ clang-13 --target=arm64-apple-macos11 --sysroot=sysroot-macos-arm64 -fuse-ld=lld -o hello hello.c
$ file hello
hello: Mach-O 64-bit arm64 executable, flags:<NOUNDEFS|DYLDLINK|TWOLEVEL|PIE>
```

Note that Clang 13 or higher is required, as older versions do not have a usable MachO linker.

## Building

Simply run:

```
make
```

This builds both the x86\_64 and the arm64 sysroots and should therefore cover most Macs.

## How it works

A libc comes in two parts: a set of header files and a binary libc that the linker will link against. Normally, you'd use the header files and a binary libc from your operating system. That of course won't work here: we will need to cross compile. Cross compiling usually means that you have to copy the important files (the header files and the libc) into a directory that you can then point your compiler and linker to. This is called a sysroot.

This is unfortunately not easily possible on macOS: while the header files are open source, the binary libc (called `libSystem.B.dylib`) probably is not.

The way this minimal SDK works around this is by first creating the header files from the individual libc components (downloaded from [opensource.apple.com](https://opensource.apple.com/)) and then constructing a fake `libSystem.B.dylib` that only contains a list of function names without an implementation. You can't use this `libSystem.B.dylib` to run an actual binary, but you can use it to link binaries against.

### Why would you do this?

It may be useful when you develop software on Linux or Windows but want to build it for MacOS. One example might be CI: Linux is currently still more widely available (and usually cheaper!) than MacOS VMs.

## Updating

To update the header files to a newer version, follow these steps.

  1. Update the version numbers in versions.inc.
  2. Run `./update.sh`. This downloads the new headers. You may need to fix build breakage especially when moving to a newer macOS version.
  3. Run `make` to build the new sysroots. This should be very quick.

This is only rarely needed: macOS binaries will usually run just fine on a newer version of the OS.

## License

This project is licensed under APSL 2.0, a variety of BSD style licenses, and public domain code:

  * `src/usr/include` is extracted from the Libc, xnu, libpthread, Libm, and CarbonHeaders. The source files are under a mix of the APSL 2.0 and a variety of BSD-style licenses. There are a few files that just say "all rights reserved". All those files have been replaced with a public domain version so they are also in effect open source.
  * `src/*/libSystem.s` is extracted from the above, but because it's only a list of function names I don't believe it is covered by copyright and therefore can be considered public domain. If it is covered by copyright (I'm not a lawyer), it is covered by the same copyright as `src/usr/include` above.
  * Other files like the various update scripts are placed in the public domain.

In other words, as far as I can see, this means that the resulting code can be freely shared and linked against.

## More information

  * https://adrummond.net/posts/macho provides some insights into the MachO file format.
