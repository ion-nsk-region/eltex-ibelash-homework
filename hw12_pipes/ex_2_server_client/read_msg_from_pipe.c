#include "mypipe2.h"

int read_msg_from_pipe(char *pipe_path, int conn_timeout, char *msg) {
  int err = 0, pipe_fd, n_attempts = 0;
  ssize_t bytes_read = 0;

  do {
    errno = 0;
    pipe_fd = open(pipe_path, O_RDONLY | O_NONBLOCK);
    if (-1 == pipe_fd && ENOENT != errno) {
      perror("open");
      err = -1;
    } else if (ENOENT == errno) {
      err = ENOENT;
    }
    if (0 == err) {
      errno = 0;
      bytes_read = read(pipe_fd, msg, PIPE_BUF);
      printf("\nDEBUG %s\n", msg);
      if (-1 == bytes_read && EAGAIN != errno) {
        perror("read");
        err = -1;
      }
    }

    if ((0 == err && 0 == bytes_read) || ENOENT == err) {
      sleep(SLEEP_TIME);
      err = conn_timer(conn_timeout, n_attempts++);
    }
  } while ((0 == err && 0 == bytes_read) || ENOENT == err);

  if (ENOENT != errno) {
    err -= close_pipe(pipe_fd);
  }

  return err;
}
