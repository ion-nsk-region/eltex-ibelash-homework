#include <ex_1.h>

void createFile(char *filename, int *fd) {
    errno = 0;

    *fd = open(filename, 
                    O_CREAT|O_WRONLY|O_TRUNC, 
                    S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP);

    if(-1 == *fd && 0 != errno) {
        perror("open");
    }
}
