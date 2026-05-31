#include "mq_chat.h"

int read_mq_msg(int mq_id, long msg_type, struct chat_msg **msg) {
  int err = 0;
  size_t max_msg_size = get_max_msg_size();
  struct msgbuf *msg_buf;

  if (-1 != mq_id) {
    errno = 0;
    msg_buf = malloc(sizeof(struct msgbuf) + max_msg_size);
    if (NULL == msg_buf) {
      err = errno;
      perror("malloc");
    }
  }

  errno = 0;
  if (0 == err &&
      -1 == msgrcv(mq_id, msg_buf, max_msg_size, msg_type, 0)) {
    err = errno;
    perror("msgrcv");
  }

  // упаковываем в целевую структуру
  if (0 == err) {
    errno = 0;
    *msg = malloc(sizeof(struct chat_msg));
    if (NULL == *msg) {
      err = errno;
      perror("malloc");
    } else {
      deserialize_msg(msg_buf->mdata, msg_buf->msize, *msg);
    }
  }

  free(msg_buf);

  return err;
}
