#include "shm_chat.h"

void destroy_semaphore(sem_t *sem4_id, const char *sem4_name) {
  errno = 0;
  int err = sem_close(sem4_id);
  if (-1 == err) {
    perror("destroy_semaphore > sem_close");
  }

  errno = 0;
  err = sem_unlink(sem4_name);
  if (-1 == err) {
    perror("destroy_semaphore > sem_unlink");
  }
}
