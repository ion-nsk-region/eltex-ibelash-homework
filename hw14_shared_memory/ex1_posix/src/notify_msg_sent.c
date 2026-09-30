#include "shm_chat.h"

int notify_msg_sent(sem_t *sem4_id) {
  errno = 0;
  int err = sem_post(sem4_id);
  if (-1 == err) {
    perror("sem_post");
  }

  return err;
}
