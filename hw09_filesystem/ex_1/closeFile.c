#include "ex_1.h"

void closeFile(int fd) {
    int ret;
    errno = 0;

    ret = close(fd);
    if(-1 == ret && 0 != errno) {
        perror("close");
    }
}
