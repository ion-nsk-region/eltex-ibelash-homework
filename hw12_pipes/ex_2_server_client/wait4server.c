#include "mypipe2.h"

int wait4server(char *pipe_path, int conn_timeout, int *pipe_fd) {
  int err = 0, is_server_up = 0, n_attempts = 0;
  char tmp_buf[PIPE_BUF];
  *pipe_fd = -2;

  do {
    // Ожидаем если файл FIFO не существует,
    // или если к нему никто не подключен на запись
    errno = 0;
    if (0 > *pipe_fd) {
      *pipe_fd = open(pipe_path, O_RDONLY | O_NONBLOCK);
    }
    if ((-1 == *pipe_fd && ENOENT == errno) ||
        (0 == read(*pipe_fd, tmp_buf, PIPE_BUF) && 0 == errno)) {
      sleep(SLEEP_TIME);
      err = conn_timer(conn_timeout, n_attempts++);  // возвращает 0 или ETIME
    } else if (-1 == *pipe_fd && ENOENT != errno) {
      perror("open");
      err = -1;
    } else {
      is_server_up = 1;
    }
  } while (0 == is_server_up && 0 == err);

  if (0 == err && 0 < *pipe_fd) {
    // сбрасываем неблокирующий режим, чтобы можно было прочитать данные.
    errno = 0;
    err = fcntl(*pipe_fd, F_SETFL, fcntl(*pipe_fd, F_GETFL) & ~O_NONBLOCK);
    if (-1 == err && 0 != errno) {
      perror("fcntl");
    }
  }
  return err;
}
