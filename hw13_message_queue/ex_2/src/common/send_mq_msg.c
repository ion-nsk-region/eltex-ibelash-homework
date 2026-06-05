#include "mq_chat.h"

int send_mq_msg(int mq_id, long to_whom, struct chat_msg msg) {
  int err = 0;
  // вычисляем размер данных и выделяем память для буфера
  size_t content_size = 0;
  if (NULL != msg.content) {
    content_size = strlen(msg.content) + 1;
  }
  size_t total_msg_size =
      sizeof(pid_t) + sizeof(enum chat_command) + content_size;
  errno = 0;
  struct msgbuf *msg_buf = malloc(sizeof(struct msgbuf) + total_msg_size);
  if (NULL == msg_buf) {
    err = errno;
    perror("malloc");
  }

  // записываем данные в буфер
  if (0 == err) {
    msg_buf->mtype = to_whom;
    msg_buf->msize = total_msg_size;
    serialize_msg(&msg, content_size, msg_buf->mdata);

    // отправляем сообщение
    // int flags = IPC_NOWAIT;
    int flags = 0;
    errno = 0;
    if (-1 == msgsnd(mq_id, msg_buf, sizeof(msg_buf->msize) + msg_buf->msize,
                     flags)) {
      perror("msgsnd");
      err = errno;
    }
  }

  // удаляем буфер
  if (NULL != msg_buf) {
    free(msg_buf);
    msg_buf = NULL;
  }

  return err;
}
