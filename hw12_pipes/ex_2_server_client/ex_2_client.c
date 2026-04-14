#include "mypipe2.h"

int main(void) {
  int err;
  int conn_timeout = CONNECTION_TIMEOUT;
  char msg[PIPE_BUF] = "";

  err = read_msg_from_pipe(PIPE_PATH, conn_timeout, msg);
  if (0 == err) {
    // Вывод сообщения
    printf("%s\n", msg);
  } else if (ETIME == err) {
    printf(
        "Ошибка: не удалось получить сообщение через канал.\n"
        "Время ожидания сервера истекло.\nВыходим.\n");
  } else if (ENOENT == err) {
    printf(
        "Ошибка: не удалось получить сообщение через канал.\n"
        "Канал не существует.\nВыходим.\n");
  } else {
    printf(
        "Ошибка: не удалось получить сообщение через канал. Код ошибки %d.\n"
        "См. подробности в stderr.\nВыходим.\n",
        err);
  }

  if (-1 == (err = delete_pipe(PIPE_PATH))) {
    printf(
        "Ошибка: не удалось удалить канал. Код ошибки %d.\n"
        "См. подробности в stderr.\nВыходим.\n",
        err);
  }

  return err;
}
