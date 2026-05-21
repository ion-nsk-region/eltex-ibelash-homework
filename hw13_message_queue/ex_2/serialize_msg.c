#include "mq_chat.h"

void serialize_msg(struct mq_msg msg, char *msg_buffer) {
  size_t offset = 0;
  memcpy(msg_buffer + offset, &msg.sender_pid, sizeof(pid_t));
  offset += sizeof(pid_t);
  memcpy(msg_buffer + offset, &msg.mtext_size, sizeof(long int));
  offset += sizeof(long int);
  memcpy(msg_buffer + offset, msg.mtext, msg.mtext_size);
}
