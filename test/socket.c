// This file is placed in the public domain.

// Check that the socket family of functions can be compiled and linked, and
// that the CMSG_* control message macros expand correctly.

#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

int main(void) {
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd < 0) {
        perror("socket");
        return 1;
    }
    struct sockaddr_storage addr = {0};
    addr.ss_family = AF_INET;
    if (connect(fd, (const struct sockaddr *)&addr, sizeof(addr)) != 0) {
        perror("connect");
    }

    // Send a file descriptor over the socket, to check the CMSG_* macros.
    char cbuf[CMSG_SPACE(sizeof(int))];
    struct msghdr msg;
    memset(&msg, 0, sizeof(msg));
    msg.msg_control = cbuf;
    msg.msg_controllen = sizeof(cbuf);
    struct cmsghdr *cmsg = CMSG_FIRSTHDR(&msg);
    cmsg->cmsg_level = SOL_SOCKET;
    cmsg->cmsg_type = SCM_RIGHTS;
    cmsg->cmsg_len = (unsigned int)CMSG_LEN(sizeof(int));
    memcpy(CMSG_DATA(cmsg), &fd, sizeof(int));
    if (CMSG_NXTHDR(&msg, cmsg) != NULL) {
        printf("unexpected second control message\n");
    }
    if (sendmsg(fd, &msg, 0) < 0) {
        perror("sendmsg");
    }

    close(fd);
    return 0;
}
