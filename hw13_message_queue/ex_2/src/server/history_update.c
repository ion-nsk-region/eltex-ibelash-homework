#include "mq_chat.h"

void history_update(struct chat_msg msg, struct chat_msg *history,
                    int *last_msg_id) {
  // рассчитываем новый индекс последнего сообщения
  *last_msg_id = (*last_msg_id + 1) % MAX_HISTORY_SIZE;

  // удаляем предыдущее содержимое
  struct chat_msg *last_msg = history + *last_msg_id;
  if (NULL != last_msg->content) free(last_msg->content);

  // записываем новое содержимое
  last_msg->sender = msg.sender;
  last_msg->cmd = msg.cmd;
  last_msg->content = msg.content;
}
