#include "mypipe2.h"

#define MSG_TO_SEND "Hi!"

int main(void) {
  int err;
  int conn_timeout = 60;  // время ожидания подключения

  err = create_pipe(PIPE_PATH);
  if (0 > err) {
    printf(
        "Ошибка: не удалость создать канал для передачи сообщения.\n"
        "Код ошибки: %d. См. подробности в stderr.\nВыходим.\n",
        err);
  } else if (0 == err) {
    if (-1 == (err = send_msg_to_pipe(PIPE_PATH, conn_timeout, MSG_TO_SEND))) {
      printf(
          "Ошибка: не удалось отправить сообщение через канал.\n"
          "См. подробности в stderr.\nВыходим.");
    } else if (ETIME == err) {
      printf(
          "Ошибка: не удалось отправить сообщение через канал.\n"
          "Время ожидания клиента истекло.\nВыходим.");
    }
  }

  return err;
}
