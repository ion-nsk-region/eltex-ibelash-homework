#include "common.h"

int send_msg(struct chat_msg *shm_addr, struct chat_msg msg, sem_t *sem4_input_updated, sem_t *sem4_input_read) {
  int err = 0;

  if (NULL == shm_addr) {
    err = -1;
  }

  wait_for(sem4_input_read);

  if (0 == err) {
    shm_addr->sender = msg.sender;
    shm_addr->cmd = msg.cmd;
    shm_addr->msg_size = msg.msg_size;
    size_t content_size = strlen(msg.content);
    strncpy(shm_addr->content, msg.content, content_size);
  }

  sem_post(sem4_input_updated);

  return err;
}
