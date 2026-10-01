#include "shm_chat.h"

void cleanup_client(sem_t *sem4_server, sem_t *sem4_client) {
  close_semaphore(sem4_server);
  close_semaphore(sem4_client);
}
