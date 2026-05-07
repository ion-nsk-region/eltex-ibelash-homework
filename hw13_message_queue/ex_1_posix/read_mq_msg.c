#include "mq_chat.h"

int read_mq_msg(mqd_t mq_id, char **msg) {
  int err = 0;
  long msg_size = 0;
  struct mq_attr attr;

  errno = 0;
  if (-1 == (err = mq_getattr(mq_id, &attr))) {
    perror("mq_getattr");
  } else if (0 == err) {
    msg_size = attr.mq_msgsize;
    errno = 0;
    *msg = (char *)malloc(msg_size);
    if (NULL == *msg) {
      perror("malloc");
      err = -1;
    }
  }

  if (0 == err) {
    errno = 0;
    if (-1 == mq_receive(mq_id, *msg, msg_size, NULL)) {
      perror("msgrcv");
      err = errno;
    }
  }

  return err;
}
