#include "mq_chat.h"

int clear_mq(char *mq_name) {
  int err = 0;
  int mq_id = -1;
  struct msgbuf *msg_buf = NULL;
  size_t max_msg_size = get_max_msg_size();
  size_t buffer_size;

  if (0 != (err = connect2mq(mq_name, &mq_id))) {
    printf(
        "Ошибка connect2mq: Не удалось подключиться к очереди %s. "
        "См. подробности в stderr.",
        mq_name);
  }

  if (0 == err && -1 != mq_id) {
    buffer_size = sizeof(struct msgbuf) + max_msg_size;      
    errno = 0;
    msg_buf = malloc(buffer_size);
    if (NULL == msg_buf) {
      err = errno;
      perror("malloc");
    }
  }

  if (0 == err && -1 != mq_id) {
    int msg_flags = IPC_NOWAIT | MSG_NOERROR;
    while (0 == is_mq_empty(mq_id, NULL) && 0 == err) {
      errno = 0;
      if (-1 == msgrcv(mq_id, msg_buf, buffer_size, 0, msg_flags) &&
          ENOMSG != errno) {
        perror("msgrcv");
        err = -1;
      }
    }
  }

  if(NULL != msg_buf) free(msg_buf);

  return err;
}
