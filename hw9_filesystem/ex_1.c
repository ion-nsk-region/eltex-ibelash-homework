#include <stdio.h>
#include <ex_1.h>

int main(void) {
    char *string_in, 
         *string_out = "String from file",
         *filename = "output.txt";
    int fd = 0;

    createFile(filename, &fd);
    write2File(fd, string_out);
    readFromFileEnd(fd, string_in);

    close(fd);

    printf("%s\n", string_in);

    return 0;
}
