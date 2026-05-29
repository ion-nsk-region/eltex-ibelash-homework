#include "mq_chat.h"

int server_queue_handler_exit(int server_mq_id) {
  int err = 0;
  struct msgbuf msg;
  msg.mtype = 1;
  msg.sender_pid = getpid();
  msg.mtext_size = sizeof(":quit");
  msg.mtext = ":quit";

  if (0 != (err = send_mq_msg(server_mq_id, msg))) {
    printf(
        "Ошибка: не удалось отправить сообщение потоку о выходе. "
        "См. подробности в stderr.\n");
  }

  return err;
}
