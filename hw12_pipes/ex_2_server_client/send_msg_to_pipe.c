#include <string.h>

#include "mypipe2.h"

int send_msg_to_pipe(char *pipe_path, int connection_timeout, char *msg) {
  int err = 0, pipe_fd;
  size_t msg_length = strlen(msg);

  // для простоты рассматриваем только атомарную запись (< PIPE_BUF)
  if (PIPE_BUF < msg_length) {
    fprintf(stderr,
            "Ошибка: сообщение слишком длинное. "
            "Пожалуйста, передайте сообщение покороче.\n");
    err = -1;
  }

  if (0 == err) {
    int n_attempts = 0;
    do {  // пытаемся открыть канал на запись пока
          // не истечёт время ожидания клиента или не случится ошибка
      errno = 0;
      pipe_fd = open(pipe_path, O_WRONLY | O_NONBLOCK);
      if (-1 == pipe_fd && ENXIO != errno) {
        perror("open");
        err = -1;
      } else if (0 == err && 0 == errno) {
        printf("\nDEBUG: Успешно подключились.\n");
      }
      if (0 == err) {
        sleep(SLEEP_TIME);
        err = conn_timer(connection_timeout, n_attempts++);
      }
    } while (ENXIO == errno && 0 == err);
  }

  if (0 == err) {
    printf("\nDEBUG: Пишем: %s\n", msg);
    errno = 0;
    ssize_t bytes_written = write(pipe_fd, msg, msg_length);
    printf("\nDEBUG: bytes_written %ld\n", bytes_written);
    if (-1 == bytes_written) {
      perror("write");
      err = -1;
    } else if (0 < bytes_written) {
      printf("\nDEBUG: записали %s\n", msg);
    } else {
      printf("\nDEBUG: Не записали\n");
    }
  }
  // close_pipe(pipe_fd);

  return err;
}
