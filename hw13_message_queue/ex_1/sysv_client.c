#include "mq_chat.h"

int main(void) {
  int err = 0;

  char *mq_name = "./sysv_server.exe";
//  char *msg = "", *reply = "Hello!";

  int mq_id;

  // подключаемся к очереди
  err = connect2mq(mq_name, &mq_id);
  if (ETIME == err) {
    printf("Ошибка: время ожидания сервера истекло.\n");
  } else if (0 != err) {
    printf("Ошибка connect2mq: %d\nСм. подробности в stderr.\n", err);
  }

  /*
  // считываем сообщение и выводим на экран
  if (0 == err && (0 != (err = read_mq_msg(mq_id, &msg)))) {
    printf("Ошибка read_mq_msg: %d\n", err);
  } else {
    printf("%s\n", msg);
  }

  // отвечаем серверу
  if (0 == err && (0 != (err = send_mq_msg(mq_id, reply)))) {
    printf("Ошибка send_mq_msg: %d\n", err);
  }
*/

  // выходим
  printf("Выходим.\n");
  return err;
}
