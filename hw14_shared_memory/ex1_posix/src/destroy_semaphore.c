#include "shm_chat.h"

void destroy_semaphore(sem_t *sem4_id, const char *sem4_name) {
  int err = close_semaphore(sem4_id);

  errno = 0;
  err = sem_unlink(sem4_name);
  if (-1 == err) {
    perror("destroy_semaphore > sem_unlink");
  }
}
