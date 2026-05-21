#include "mq_chat.h"

unsigned char *allocate_msg_buffer(mqd_t mq_id, long *msg_buffer_size) {
  struct mq_attr attr;
  unsigned char *msg_buffer = NULL;
  int err = 0;

  if (NULL == msg_buffer_size) {
    fprintf(stderr, "Ошибка allocate_msg_buffer: Не указана переменная для передачи размера выделенного буфера.\n");
    err = -1;
  }
  if (0 == err && 0 >= *msg_buffer_size) {
    errno = 0;
    if (0 == mq_getattr(mq_id, &attr)) {
      *msg_buffer_size = attr.mq_msgsize;
    } else {
      perror("mq_getattr");
      err = -1;
    }
  }
  if (0 == err && 0 < *msg_buffer_size) {
    errno = 0;
    msg_buffer = (unsigned char *)malloc(*msg_buffer_size);
    if (NULL == msg_buffer) {
      perror("malloc");
      err = -1;
    }
  }

  return msg_buffer;
}
