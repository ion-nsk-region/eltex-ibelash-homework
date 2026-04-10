#include "ex_1.h"

int create_pipe(int *my_pipe) {
  int err = 0;

  errno = 0;
  if (-1 == (err = pipe(my_pipe))) {
    perror("pipe");
  }

  return err;
}
