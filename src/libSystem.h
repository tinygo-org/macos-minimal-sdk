// Include all header files for libSystem.dylib, so all the stubs are
// generated. Add more headers as needed.

#include <dirent.h>
#include <fcntl.h>
#include <math.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/errno.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/sysctl.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

// These symbols must be declared manually.
extern char **environ;

// These symbols are internal and must therefore be declared manually.
int __ulock_wait(uint32_t operation, void *addr, uint64_t value, uint32_t timeout_us);
int __ulock_wait2(uint32_t operation, void *addr, uint64_t value, uint64_t timeout_ns, uint64_t value2);
int __ulock_wake(uint32_t operation, void *addr, uint64_t wake_value);
