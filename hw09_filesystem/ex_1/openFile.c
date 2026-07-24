#include "ex_1.h"

void openFile(const char *filename, int flags, int *fd) {
    errno = 0;

    *fd = open(filename, flags);

    if(-1 == *fd && 0 != errno) {
        perror("open");
    }
}
