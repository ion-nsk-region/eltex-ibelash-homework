#include "mq_chat.h"

int is_mq_empty(int mq_id, long unsigned int *mq_num) {
  int res = 0;
  struct msqid_ds mq_ds;

  errno = 0;
  if (-1 == msgctl(mq_id, IPC_STAT, &mq_ds)) {
    perror("msgctl");
    res = -1;
  } else {
    *mq_num = mq_ds.msg_qnum;
    if (0 == *mq_num) res = 1;
  }

  return res;
}
