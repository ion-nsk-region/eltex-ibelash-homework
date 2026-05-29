#include "mq_chat.h"

int send_mq_msg(int mq_id, struct msgbuf *msg) {
  int err = 0;
  long total_msg_size = sizeof(struct msgbuf) + msg->mtext_size;

  errno = 0;
  if (-1 == msgsnd(mq_id, msg, total_msg_size, 0)) {
    perror("msgsnd");
    err = errno;
  }

  return err;
}
