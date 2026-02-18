#include <string.h>
#include "ex_1.h"

void write2File(const char *filename, const char *string_out) {
    ssize_t written_length, str_length = (ssize_t)strlen(string_out);
    int fd;

    openFile(filename, O_WRONLY|O_SYNC, &fd);

    errno = 0;
    written_length = write(fd, string_out, str_length);
    if (-1 == written_length && 0 != errno) {
        perror("write");
    }

    closeFile(fd);
}
