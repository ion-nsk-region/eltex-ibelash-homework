#include "shm_chat.h"

void cleanup(void *shm_addr) {
  key_t key = ftok(SERVER_FILENAME, PROJ_ID);
    
  errno = 0;
  int sem4_id = semget(key, 1, 0);
  if (-1 == sem4_id) {
    perror("semget");
  }
  destroy_semaphore(sem4_id);

  detach_shm_segment(shm_addr);

  errno = 0;
  int shm_id = shmget(key, 1, 0);
  if (-1 == shm_id) {
    perror("shmget");
  }
  destroy_shm_segment(shm_id);
}
