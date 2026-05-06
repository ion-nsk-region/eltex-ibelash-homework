#include "mq_chat.h"

int connect2mq(char *mq_name, int mq_flags, mqd_t *mq_id) {
  int err = 0;

  if (NULL != mq_name) {
      int n_attempts = 0;
      do {
        errno = 0;
        if (0 == mq_flags & O_CREAT) {
        *mq_id = mq_open(mq_name, mq_flags);
        } else {
        mode_t mq_perm = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP;
        *mq_id = mq_open(mq_name, mq_flags, mq_perm, NULL);
        }
      } while (-1 == *mq_id && ENOENT == errno &&
               ETIME != (err = conn_timer(CONNECTION_TIMEOUT, SLEEP_TIME,
                                          n_attempts++)));

      if (-1 == *mq_id && ETIME != err) {
        perror("mq_open");
        err = -1;
      }
  }

  return err;
}
