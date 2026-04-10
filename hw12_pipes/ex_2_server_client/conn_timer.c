#include "mypipe2.h"

int conn_timer(int connection_timeout, int n_attempts) {
  int err = 0;
  if (connection_timeout < n_attempts * SLEEP_TIME) {
    err = ETIME;
  }
  return err;
}
