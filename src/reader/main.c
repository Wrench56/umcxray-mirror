#include <stdio.h>

#include <unistd.h>
#include <fcntl.h>

#include "atlxray.h"

#define ATLXRAY_DEBUGFS_PATH "/sys/kernel/debug/atlxray/regs"

int main(void) {
    printf("Hello World!\n");

    if (access(ATLXRAY_DEBUGFS_PATH, F_OK) != 0)
    {
        perror("access() failed!");
        return 1;
    }

    int fd = open(ATLXRAY_DEBUGFS_PATH, O_RDONLY, NULL);
    if (fd == 0)
    {
        perror("open() failed!");
        return 1;
    }

    struct atl_regs regs = { 0 };
    if (read(fd, &regs, sizeof(regs)) != sizeof(regs))
    {
        perror("read() failed!");
        return 1;
    }

    if (regs.magic != ATL_MAGIC)
    {
        perror("Magic check failed!");
        return 1;
    }

    return 0;
}
