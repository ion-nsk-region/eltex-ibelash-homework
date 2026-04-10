#include "ex_1.h"

ssize_t read_msg_from_pipe(int *my_pipe, char *msg) {
  ssize_t count;

  errno = 0;
  count = read(my_pipe[0], msg, BUFSIZ);
  if (-1 == count) {
    perror("read");
  }

  return count;
}
