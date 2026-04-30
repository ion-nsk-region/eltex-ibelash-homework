#include "mq_chat.h"

int conn_timer(int connection_timeout, int sleep_time, int n_attempts) {
  int err = 0;
  if (connection_timeout < sleep_time * n_attempts) {
    err = ETIME;
  } else {
    sleep(sleep_time);
  }

  return err;
}

