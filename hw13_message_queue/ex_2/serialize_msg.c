#include "mq_chat.h"

void serialize_msg(struct chat_msg *msg, size_t content_size, char *mdata) {
  size_t offset = 0;
  memcpy(mdata + offset, &msg->sender, sizeof(pid_t));
  offset += sizeof(pid_t);
  memcpy(mdata + offset, &msg->cmd, sizeof(enum chat_command));
  offset += sizeof(enum chat_command);
  memcpy(mdata + offset, msg->content, content_size);
}
