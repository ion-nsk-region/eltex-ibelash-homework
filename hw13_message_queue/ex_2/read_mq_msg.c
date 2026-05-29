#include "mq_chat.h"

int read_mq_msg(int mq_id, long msg_type, struct msgbuf **msg) {
  int err = 0;
  long max_msg_size = get_max_msg_size();
  struct msgbuf *msg_buf;
  ssize_t bytes_read;

  if (-1 != mq_id) {
    msg_buf = malloc(sizeof(struct msgbuf));
    if (NULL == msg_buf) {
      printf(
          "Не удалось выделить память под буфер чтения сообщений. "
          "См. подробности в stderr.\n");
      err = -1;
    } else {
        msg_buf->mtext = calloc(1, max_msg_size * sizeof(char));
    }
  }

  errno = 0;
  if (-1 == (bytes_read = msgrcv(mq_id, msg_buf, max_msg_size, msg_type, 0))) {
    perror("msgrcv");
    err = errno;
  }
  printf(
      "read_mq_msg прочитано:\n mtype = %ld,\n pid = %d,\n text_size = %ld,\n text = %s.\n",
      msg_buf->mtype, msg_buf->sender_pid, msg_buf->mtext_size, msg_buf->mtext);

  if (0 == err) {
    *msg = calloc(1, sizeof(struct msgbuf));
    if (NULL != msg) {
      (*msg)->mtype = msg_buf->mtype;
      (*msg)->sender_pid = msg_buf->sender_pid;
      (*msg)->mtext_size = msg_buf->mtext_size;
      (*msg)->mtext = strndup(msg_buf->mtext, msg_buf->mtext_size);
    } else {
      fprintf(stderr, "Ошибка: не удалось выделить память под сообщение.\n");
      err = ENOMEM;
    }
  }

  free_msg_buffer(msg_buf);

  return err;
}
