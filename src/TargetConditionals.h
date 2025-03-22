// This file is placed in the public domain.
//
// This file is a replacement for TargetConditionals.h for which I can't find an
// open source version in an open source Apple library. (There is one in
// CarbonHeaders but it is outdated doesn't support ARM64).

#define TARGET_CPU_PPC          0
#define TARGET_CPU_PPC64        0
#define TARGET_CPU_68K          0
#define TARGET_CPU_X86          0
#define TARGET_CPU_X86_64       defined(__x86_64__)
#define TARGET_CPU_ARM          0
#define TARGET_CPU_ARM64        defined(__arm64__)
#define TARGET_CPU_MIPS         0
#define TARGET_CPU_SPARC        0
#define TARGET_CPU_ALPHA        0

// We only support macOS (OSX) right now.
#define TARGET_OS_WIN32       0
#define TARGET_OS_WINDOWS     0
#define TARGET_OS_UNIX        0
#define TARGET_OS_LINUX       0
#define TARGET_OS_MAC         1
#define TARGET_OS_OSX         1
#define TARGET_OS_IPHONE      0
#define TARGET_OS_IOS         0
#define TARGET_OS_MACCATALYST 0
#define TARGET_OS_TV          0
#define TARGET_OS_WATCH       0
#define TARGET_OS_VISION      0
#define TARGET_OS_BRIDGE      0
#define TARGET_OS_SIMULATOR   0
#define TARGET_OS_DRIVERKIT   0
