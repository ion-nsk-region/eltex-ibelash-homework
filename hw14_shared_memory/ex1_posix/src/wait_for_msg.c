#include "shm_chat.h"

int wait_for_msg(sem_t *sem4_id) {
  errno = 0;
  int err = sem_wait(sem4_id);
  if (-1 == err) {
    perror("sem_wait");
  }

  return err;
}
