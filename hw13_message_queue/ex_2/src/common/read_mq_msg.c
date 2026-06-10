#include "mq_chat.h"

int read_mq_msg(int mq_id, long msg_type, struct chat_msg **msg) {
  int err = 0;
  size_t max_msg_size = get_max_msg_size();
  struct msgbuf *msg_buf = NULL;

  if (-1 != mq_id) {
    errno = 0;
    msg_buf = malloc(sizeof(long) + max_msg_size);
    if (NULL == msg_buf) {
      err = errno;
      perror("malloc");
    }
  } else {
    err = -1;
  }

  pthread_cleanup_push(cleanup_buffer, msg_buf);
  errno = 0;
  if (0 == err && -1 == msgrcv(mq_id, msg_buf, max_msg_size, msg_type, 0)) {
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
      pthread_cleanup_push(cleanup_buffer, *msg);
      pthread_cleanup_push(cleanup_buffer, (*msg)->content);
      deserialize_msg(msg_buf->mdata, msg_buf->msize, *msg);
      // освобождаем только в случае падения
      pthread_cleanup_pop(0);  // *(msg)->content
      pthread_cleanup_pop(0);  // msg
                               /*
                                * const char *commands[] = {"NO_COMMAND", "JOIN",    "QUIT",
                                                               "LIST",       "HISTORY", "MSG"};
                                     fprintf(stderr,
                                             "DEBUG Получено от %d к %ld, команда %s,\n"
                                             "содержимое %s.\n",
                                             (*msg)->sender, msg_type, commands[(*msg)->cmd],
                                (*msg)->content);
                                 */
    }
  }

  pthread_cleanup_pop(1);  // освобождаем msg_buf в любом случае

  return err;
}
