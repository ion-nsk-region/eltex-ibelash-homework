#include <stdlib.h>

#include "shm_chat.h"

void cleanup(void *shm_addr, sem_t *sem4_server, sem_t *sem4_client,
             char *reply) {
  unsigned long page_size = sysconf(_SC_PAGESIZE);

  destroy_semaphore(sem4_server, SEM4_SERVER);
  destroy_semaphore(sem4_client, SEM4_CLIENT);
  detach_shm_segment(shm_addr, page_size);
  destroy_shm_segment(SHM_FILENAME);
  free(reply);
}
