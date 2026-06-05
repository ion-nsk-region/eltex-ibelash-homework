#include "mq_chat.h"

int delete_mq(int mq_id) {
  int err = 0;

  errno = 0;
  if (-1 == msgctl(mq_id, IPC_RMID, NULL)) {
    perror("msgctl");
    err = -1;
  }

  return err;
}
