#include "mq_chat.h"

unsigned char *allocate_msg_buffer(long *msg_buffer_size) {
  long max_msg_size = get_max_msg_size();
  unsigned char *msg_buffer = NULL;
  int err = 0;

  if (NULL == msg_buffer_size) {
    fprintf(stderr,
            "Ошибка allocate_msg_buffer: Не указана переменная для передачи "
            "размера выделенного буфера.\n");
    err = -1;
  }
  if (0 == err && (0 >= *msg_buffer_size || max_msg_size < *msg_buffer_size)) {
    *msg_buffer_size = max_msg_size;
  }

  if (0 == err) {
    errno = 0;
    msg_buffer = (unsigned char *)malloc(*msg_buffer_size);
    if (NULL == msg_buffer) {
      perror("malloc");
    }
  }

  return msg_buffer;
}
