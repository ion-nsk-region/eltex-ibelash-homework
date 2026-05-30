#include "mq_chat.h"

int read_mq_msg(int mq_id, long msg_type, struct chat_msg **msg) {
  int err = 0;
  size_t max_msg_size = get_max_msg_size();
  struct msgbuf *msg_buf;
  ssize_t bytes_read;

  if (-1 != mq_id) {
    msg_buf = malloc(sizeof(struct msgbuf) + max_msg_size);
    if (NULL == msg_buf) {
      printf(
          "Не удалось выделить память под буфер чтения сообщений. "
          "См. подробности в stderr.\n");
      err = -1;
    }
  }

  errno = 0;
  if (-1 == (bytes_read = msgrcv(mq_id, msg_buf, max_msg_size, msg_type, 0))) {
    perror("msgrcv");
    err = errno;
  }

  if (0 == err) {
    *msg = malloc(msg_buf->msize);
    if (NULL != msg) {
        deserialize_msg(msg_buf->mdata, msg_buf->msize, *msg);
    } else {
      fprintf(stderr, "Ошибка: не удалось выделить память под сообщение.\n");
      err = ENOMEM;
    }
  }

  free(msg_buf);

  return err;
}
