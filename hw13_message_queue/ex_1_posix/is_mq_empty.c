#include "mq_chat.h"

int is_mq_empty(int mq_id, long int *mq_n_messages) {
  int res = 0;
  struct mq_attr attr;

  errno = 0;
  if (-1 == mq_getattr(mq_id, &attr)) {
    perror("mq_getattr");
    res = -1;
  } else if (0 == attr.mq_curmsgs) {
    res = 1;
    if (NULL != mq_n_messages) *mq_n_messages = attr.mq_curmsgs;
  }

  return res;
}
