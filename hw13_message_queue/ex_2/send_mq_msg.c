#include "mq_chat.h"

int send_mq_msg(mqd_t mq_id, const char *msg, size_t msg_length) {
  int err = 0;

  errno = 0;
  if (-1 == mq_send(mq_id, msg, msg_length, 0)) {
    perror("mq_send");
    err = errno;
  }

  return err;
}
