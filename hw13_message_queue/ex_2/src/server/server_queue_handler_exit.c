#include "server.h"

int server_queue_handler_exit(int server_mq_id) {
  int err = 0;
  struct chat_msg msg;
  msg.sender = getpid();
  msg.cmd = QUIT;
  msg.content = NULL;

  if (0 != (err = send_mq_msg(server_mq_id, 1, msg))) {
    printf(
        "Ошибка: не удалось отправить сообщение потоку о выходе. "
        "См. подробности в stderr.\n");
  }

  return err;
}
