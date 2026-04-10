#include "ex_1.h"

#define MSG_TO_SEND "Hi!"

int main(void) {
  int err = 0;
  int my_pipe[2];
  char msg[BUFSIZ] = "";

  err = create_pipe(my_pipe);
  if (0 > err) {
    printf(
        "Ошибка: не удалость создать канал для передачи сообщения.\n"
        "Код ошибки: %d. См. подробности в stderr.\nВыходим.\n",
        err);
    return err;
  }

  // порождаем дочерний процесс
  errno = 0;
  pid_t child_pid = fork();
  if (-1 == child_pid) {
    perror("fork");
    err = -1;
  } else if (0 < child_pid) {
    // родитель
    if (0 == close_pipe_end(my_pipe[0]) &&  // закрываем на чтение
        (0 <= send_msg_to_pipe(my_pipe, MSG_TO_SEND))) {
      if (-1 == (err = wait4child(child_pid))) {
        printf(
            "Ошибка при проверке состояния дочернего процесса. "
            "См. подробности в stderr.\n");
      }
    } else {
      printf(
          "Ошибка: не удалось отправить сообщение. "
          "См. подробности в stderr.\n");
      err = -2;
    }
    // больше ничего писать не будем, поэтому закрываем и на запись.
    close_pipe_end(my_pipe[1]);
  } else if (0 == child_pid) {
    // дочерний процесс
    if (0 == close_pipe_end(my_pipe[1]) &&  // закрываем на запись
        0 < read_msg_from_pipe(my_pipe, msg)) {
      printf("%s\n", msg);
    } else {
      printf(
          "Ошибка: не удалось прочитать сообщение. "
          "См. подробности в stderr.\n");
      err = -3;
    }
    // больше ничего читать не будем, поэтому закрываем окончательно
    close_pipe_end(my_pipe[0]);
  }

  return err;
}
