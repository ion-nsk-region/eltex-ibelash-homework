#include "server.h"

void history_update(struct chat_msg *msg, struct chat_msg *history,
                    sem_t *input_read) {
  // рассчитываем новый индекс последнего сообщения

  // удаляем предыдущее содержимое
  struct chat_msg *last_msg = history + *last_msg_id;

  // записываем новое содержимое
  last_msg->msg_size = msg->msg_size;
  last_msg->sender = msg->sender;
  last_msg->cmd = msg->cmd;
  size_t content_length = strlen(msg->content);
  strncpy(last_msg->content, msg->content, content_length);


  sem_post(input_read);
}
