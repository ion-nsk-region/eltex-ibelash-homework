#include "mypipe2.h"

int create_pipe(char *my_pipe) {
  int err = 0;
  mode_t ug_rw_mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP;

  errno = 0;
  if (-1 == mkfifo(my_pipe, ug_rw_mode) && EEXIST != errno) {
    perror("pipe");
    err = -1;
  }

  return err;
}
