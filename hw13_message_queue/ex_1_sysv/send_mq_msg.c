#include "mq_chat.h"

int send_mq_msg(int mq_id, const char *msg, size_t msg_length) {
  int err = 0;
  struct msgbuf msg_buf = {.mtype = 1, .mtext = ""};
  // msg_buf.mtype = 1;  // Любое число больше ноля

  strncpy(msg_buf.mtext, msg, msg_length);

  errno = 0;
  if (-1 == msgsnd(mq_id, &msg_buf, sizeof(msg_buf.mtext), 0)) {
    perror("msgsnd");
    err = errno;
  }

  return err;
}
