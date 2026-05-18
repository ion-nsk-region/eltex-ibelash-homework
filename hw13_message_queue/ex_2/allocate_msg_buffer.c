#include "mq_chat.h"

unsigned har *allocate_msg_buffer(mqd_t mq_id, long *msg_buffer_size) {
  struct mq_attr attr;
  unsigned char *msg_buffer = NULL;

  if (0 >= *msg_buffer_size) {
    errno = 0;
    if (0 == mq_getattr(mq_id, &attr)) {
      *msg_buffer_size = attr.mq_msgsize;
    } else {
      perror("mq_getattr");
    }
  }
  if (0 < msg_buffer_size) {
    errno = 0;
    msg_buffer = (unsigned char *)malloc(*msg_buffer_size);
    if (NULL == msg_buffer) {
      perror("malloc");
    }
  }

  return msg_buffer;
}
