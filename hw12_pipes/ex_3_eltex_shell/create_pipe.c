#include "eltex_shell.h"

int create_pipe(int **ptr_pipe) {
  int err = 0;
  errno = 0;
  *ptr_pipe = (int *)malloc(sizeof(int) * 2);
  if (NULL == *ptr_pipe) {
    perror("malloc");
    err = -1;
  }
  errno = 0;
  if (0 == err && -1 == pipe(*ptr_pipe)) {
    perror("pipe");
    err = -2;
  }

  return err;
}
