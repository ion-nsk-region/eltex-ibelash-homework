#include "shm_chat.h"

int close_semaphore(sem_t *sem4_id) {
  errno = 0;
  int err = sem_close(sem4_id);
  if (-1 == err) {
    perror("sem_close");
  }

  return err;
}
