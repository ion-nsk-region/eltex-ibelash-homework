#include "mq_chat.h"

int read_mq_msg(int mq_id, long msg_type, char **msg) {
  int err = 0;
  struct msgbuf msg_buf;
  ssize_t bytes_read;

  errno = 0;
  if (-1 == (bytes_read = msgrcv(mq_id, &msg_buf, MSG_LENGTH, msg_type, 0))) {
    perror("msgrcv");
    err = errno;
  }

  if (0 == err) {
    *msg = (char *)malloc(bytes_read * sizeof(char));
    if (NULL != *msg) {
      strncpy(*msg, msg_buf.mtext, bytes_read);
    } else {
      fprintf(stderr, "Ошибка: не удалось выделить память под сообщение.\n");
      err = ENOMEM;
    }
  }

  return err;
}
