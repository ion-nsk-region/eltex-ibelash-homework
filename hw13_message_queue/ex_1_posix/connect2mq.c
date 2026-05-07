#include "mq_chat.h"

int connect2mq(char *mq_name, mqd_t *mq_id) {
  int err = 0;

  if (NULL != mq_name) {
    int n_attempts = 0;
    do {
      errno = 0;
      int mq_flags = O_RDONLY | O_CLOEXEC;
      *mq_id = mq_open(mq_name, mq_flags);
    } while (-1 == *mq_id && ENOENT == errno &&
             ETIME != (err = conn_timer(CONNECTION_TIMEOUT, SLEEP_TIME,
                                        n_attempts++)));
  }

  if (-1 == *mq_id && ETIME != err) {
    perror("mq_open");
    err = -1;
  }

  return err;
}
