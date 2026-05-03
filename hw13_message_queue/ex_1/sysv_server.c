#include "mq_chat.h"

int main(void) {
  int err = 0;
  char *mq_name = "./sysv_server.exe";
  int mq_id = 0;
  char *msg = "Hi!";
  char *reply = NULL;

  // Создаём очередь
  int mq_flags = IPC_CREATE | 0660;
  err = connect2mq(mq_name, mq_flags, &mq_id);
  // Отправляем сообщение
  // Читаем ответ
  // Удаляем очередь
  // Выходим
  printf("Выходим.\n");

  return err;
}
