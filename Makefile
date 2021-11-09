include versions.inc

SYSROOTS = sysroot-macos-x86_64 sysroot-macos-arm64

CLANG ?= clang-13

DYLDFLAGS = \
    -dynamiclib \
    -fuse-ld=lld \
    -nostdlib \
    -Wl,-install_name -Wl,/usr/lib/libSystem.B.dylib \
    -Wl,-compatibility_version -Wl,1.0.0 \
    -Wl,-current_version -Wl,$(Libc_version)

.PHONY: sysroots
sysroots: $(SYSROOTS)

.PHONY: clean
clean:
	rm -rf $(SYSROOTS)

sysroot-%/usr/include: update.sh src/usr/include
	rm -rf $@
	mkdir -p $@
	cp -rp src/usr/include/* $@

sysroot-macos-x86_64: sysroot-macos-x86_64/usr/include sysroot-macos-x86_64/usr/lib/libSystem.dylib
sysroot-macos-x86_64/usr/lib/libSystem.dylib:
	mkdir -p $(dir $@)
	$(CLANG) $(DYLDFLAGS) --target=x86_64-apple-macos10.12 -o $(dir $@)/libSystem.B.dylib src/x86_64/libSystem.s
	ln -sf libSystem.B.dylib $@

sysroot-macos-arm64: sysroot-macos-arm64/usr/include sysroot-macos-arm64/usr/lib/libSystem.dylib
sysroot-macos-arm64/usr/lib/libSystem.dylib:
	mkdir -p $(dir $@)
	$(CLANG) $(DYLDFLAGS) --target=arm64-apple-macos11 -o $(dir $@)/libSystem.B.dylib src/x86_64/libSystem.s
	ln -sf libSystem.B.dylib $@

test: sysroots
	$(CLANG) --target=x86_64-apple-macos10.12 --sysroot=sysroot-macos-x86_64 -fuse-ld=lld -o hello test/hello.c
	file hello
	$(CLANG) --target=arm64-apple-macos11     --sysroot=sysroot-macos-arm64  -fuse-ld=lld -o hello test/hello.c
	file hello
