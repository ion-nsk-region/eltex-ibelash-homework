#ifndef IBELASH_EX_1_h
#define IBELASH_EX_1_h

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

void createFile(const char *filename);
void openFile(const char *filename, int flags, int *fd);
void write2File(const char *filename, const char *string_out);
void readBackwardsFromFile(const char *filename, char *string_in);
void closeFile(int fd); 

#endif // IBELASH_EX_1_h
