#include "mq_chat.h"

int free_msg_buffer(struct msgbuf *buffer) {
  int err = 0;

  if (NULL != buffer && NULL != buffer->mtext) {
    free(buffer->mtext);
    buffer->mtext = NULL;
    free(buffer);
    buffer = NULL;
  } else
    err = -1;

  return err;
}
