#include "mq_chat.h"

int delete_mq(const char *mq_name) {
  int err = 0;

  errno = 0;
  if (-1 == mq_unlink(mq_name)) {
    perror("mq_unlink");
    err = -1;
  }

  return err;
}
