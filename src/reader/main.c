#include <stdio.h>

#include <unistd.h>
#include <fcntl.h>

#include "umcxray.h"

#define UMCXRAY_DEBUGFS_PATH "/sys/kernel/debug/umcxray/regs"

int main(void) {
    printf("Hello World!\n");

    if (access(UMCXRAY_DEBUGFS_PATH, F_OK) != 0)
    {
        perror("access() failed!");
        return 1;
    }

    int fd = open(UMCXRAY_DEBUGFS_PATH, O_RDONLY, NULL);
    if (fd == 0)
    {
        perror("open() failed!");
        return 1;
    }

    struct umc_regs regs = { 0 };
    if (read(fd, &regs, sizeof(regs)) != sizeof(regs))
    {
        perror("read() failed!");
        return 1;
    }

    if (regs.magic != UMC_MAGIC)
    {
        perror("Magic check failed!");
        return 1;
    }

    return 0;
}
