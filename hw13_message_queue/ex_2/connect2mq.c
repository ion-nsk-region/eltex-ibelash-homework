#include "mq_chat.h"

int connect2mq(char *mq_name, int mq_flags, int *mq_id) {
  int err = 0;

  if (NULL != mq_name) {
    key_t key;
    errno = 0;
    if (-1 == (key = ftok(mq_name, PROJ_ID))) {
      perror("ftok");
      err = -1;
    } else {
      int n_attempts = 0;
      do {
        errno = 0;
        *mq_id = msgget(key, mq_flags);
      } while (-1 == *mq_id && ENOENT == errno &&
               ETIME != (err = conn_timer(CONNECTION_TIMEOUT, SLEEP_TIME,
                                          n_attempts++)));

      if (-1 == *mq_id && ETIME != err) {
        perror("msgget");
        err = -1;
      }
    }
  }

  return err;
}
