#include "mq_chat.h"

int clear_mq(const char *mq_name) {
  int err = 0;
  mqd_t mq_id;
  long msg_size = 0;
  unsigned char *msg = NULL;
  struct mq_attr attr;

  errno = 0;
  int mq_flags = O_RDONLY | O_CLOEXEC | O_NONBLOCK;
  if (-1 == (mq_id = mq_open(mq_name, mq_flags))) {
    perror("mq_open");
    err = -1;
  }

  if (0 == err && -1 != mq_id) {
    msg = allocate_msg_buffer(mq_id);
    if (NULL == msg) {
      printf("Не удалось выделить память под буфер чтения сообщений. См. подробности в stderr.\n");
      err = -1;
    }
  }

  if (0 == err && -1 != mq_id) {
    while (0 == is_mq_empty(mq_id, NULL) && 0 == err) {
      errno = 0;
      if (-1 == mq_receive(mq_id, msg, msg_size, NULL) && EAGAIN != errno) {
        perror("mq_receive");
        err = -1;
      }
    }
  }

  if (NULL != msg) free(msg);
  if (-1 != mq_id) mq_close(mq_id);

  return err;
}
