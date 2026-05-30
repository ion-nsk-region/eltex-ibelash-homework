#include "mq_chat.h"

int send_mq_msg(int mq_id, struct chat_msg msg) {
  int err = 0;
  // вычисляем размер данных и выделяем память для буфера
  size_t content_size = strlen(msg.content) + 1;
  size_t total_msg_size = sizeof(pid_t) + sizeof(enum chat_command) + content_size;
  struct msgbuf *msg_buf = malloc(sizeof(struct msgbuf) + total_msg_size);

  // записываем данные в буфер
  msg_buf->mtype = msg.sender;
  msg_buf->msize = total_msg_size;
  serialize_msg(&msg, content_size, msg_buf->mdata);

  printf(
      "send_mq_msg отправим:\n mtype = %ld,\n msize = %ld,\n mdata = %s.\n",
      msg_buf->mtype, msg_buf->msize, msg_buf->mdata);
  // отправляем сообщение
  errno = 0;
  if (-1 == msgsnd(mq_id, msg_buf, sizeof(msg_buf->msize) + msg_buf->msize, 0)) {
    perror("msgsnd");
    err = errno;
  }

  // удаляем буфер
  free(msg_buf);
  msg_buf = NULL;

  return err;
}
