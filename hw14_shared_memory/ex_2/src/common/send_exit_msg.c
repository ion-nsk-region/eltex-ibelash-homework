#include "common.h"

int send_exit_msg(struct chat_msg *input, sem_t *input_updated,
                  sem_t *input_read) {
  int err = 0;
  struct chat_msg msg;
  msg.sender = getpid();
  msg.cmd = QUIT;
  msg.content[0] = '\0';
  // TODO округлять размер до кратного 8, чтобы не снижало производительность
  msg.msg_size = sizeof(struct chat_msg) + 1;

  err = send_msg(input, &msg, input_updated, input_read);
  if (0 != err) {
    printf(
        "Ошибка: не удалось отправить сообщение потоку о выходе. "
        "См. подробности в stderr.\n");
  }

  return err;
}
