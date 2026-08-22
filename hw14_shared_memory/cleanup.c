#include "shm_chat.h"

void cleanup(int shm_id, void *shm_addr, int sem4_id) {
  destroy_semaphore(sem4_id);
  detach_shm_segment(shm_addr);
  destroy_shm_segment(shm_id);
}
