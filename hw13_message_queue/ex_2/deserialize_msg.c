#include "mq_chat.h"

void deserialize_msg(const char *msg_buffer, struct msgbuf *msg) {
  size_t offset = 0;
  
  printf("DEBUG: deserialize\n  mtype %ld\n", *(long int *)(msg_buffer + offset));
  memcpy(&msg->mtype, msg_buffer + offset, sizeof(long int));
  offset += sizeof(long int);
  
  printf("  sender_pid %d\n", *(pid_t *)(msg_buffer + offset));
  memcpy(&msg->sender_pid, msg_buffer + offset, sizeof(pid_t));
  offset += sizeof(pid_t);

  printf("  mtext_size %ld\n", *(long int *)(msg_buffer + offset));
  memcpy(&msg->mtext_size, msg_buffer + offset, sizeof(long int));
  offset += sizeof(long int);
  errno = 0;
  msg->mtext = malloc(msg->mtext_size);
  if (NULL == msg->mtext) {
    perror("malloc");
  } else {
    printf("  mtext %s\n", (char *)(msg_buffer + offset));
    memcpy(msg->mtext, msg_buffer + offset, msg->mtext_size);
  }
}
