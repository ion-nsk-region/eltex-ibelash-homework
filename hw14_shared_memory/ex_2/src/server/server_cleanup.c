#include "server.h"

int server_cleanup(void *input_shm_addr, sem_t *input_updated,
                   sem_t *input_read, struct user *users,
                   struct chat_msg *history, sem_t *data_updated,
                   sem_t *count_reads, sem_t *next_turn) {
  size_t page_size = (size_t)sysconf(_SC_PAGESIZE);

  destroy_semaphore(next_turn, SEM4_COUNT_READS);
  destroy_semaphore(count_reads, SEM4_COUNT_READS);
  destroy_semaphore(data_updated, SEM4_DATA_UPDATED);
  destroy_semaphore(input_read, SEM4_INPUT_READ);
  destroy_semaphore(input_updated, SEM4_INPUT_UPDATED);

  detach_shm_segment(history, page_size);
  destroy_shm_segment(SHM_HISTORY);

  detach_shm_segment(users, page_size);
  destroy_shm_segment(SHM_USERS);

  detach_shm_segment(input_shm_addr, page_size);
  destroy_shm_segment(SHM_INPUT);

  return 0;
}
