#include <string.h>

#include "ex_1.h"

ssize_t send_msg_to_pipe(int *my_pipe, char *msg) {
  size_t msg_length = strlen(msg);
  ssize_t count_written;
  if (BUFSIZ - 1 < msg_length || SSIZE_MAX - 1 < msg_length) {
    fprintf(stderr,
            "Ошибка: Сообщение слишком длинное. Пожалуйста, передайте "
            "сообщение покороче.\n");
    return -1;
  }

  errno = 0;
  if (-1 == (count_written = write(my_pipe[1], msg, msg_length))) {
    perror("write");
  }

  return count_written;
}
