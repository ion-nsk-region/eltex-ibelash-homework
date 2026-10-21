#include "server.h"

int server_queue_handler_exit(void *input_shm_addr) {
  int err = 0;
  struct chat_msg msg;
  msg.sender = getpid();
  msg.cmd = QUIT;
  msg.content = NULL;

  err = send_msg(input_shm_addr, msg);
  if (0 != err) {
    printf(
        "Ошибка: не удалось отправить сообщение потоку о выходе. "
        "См. подробности в stderr.\n");
  }

  return err;
}
