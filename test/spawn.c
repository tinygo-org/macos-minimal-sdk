// This file is placed in the public domain.

// Check that the posix_spawn family of functions can be compiled and linked.

#include <spawn.h>
#include <stdio.h>

int main(void) {
    posix_spawn_file_actions_t actions;
    posix_spawnattr_t attr;
    posix_spawn_file_actions_init(&actions);
    posix_spawn_file_actions_addclose(&actions, 0);
    posix_spawnattr_init(&attr);
    posix_spawnattr_setflags(&attr, POSIX_SPAWN_SETPGROUP);
    char *argv[] = {"true", 0};
    char *envp[] = {0};
    pid_t pid;
    int err = posix_spawn(&pid, "/usr/bin/true", &actions, &attr, argv, envp);
    if (err != 0) {
        fprintf(stderr, "posix_spawn error: %d\n", err);
    }
    posix_spawnattr_destroy(&attr);
    posix_spawn_file_actions_destroy(&actions);
    return 0;
}
