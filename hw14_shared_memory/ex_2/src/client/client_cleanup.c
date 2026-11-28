#include "client.h"

void client_cleanup(struct chat_msg **msg, sem_t **input_updated,
                    sem_t **input_read, struct user **users,
                    struct chat_history **history, sem_t **data_updated,
                    sem_t **count_reads, sem_t **next_turn,
                    const struct ui *ui) {
  if (NULL != *next_turn) close_semaphore(*next_turn);
  if (NULL != *count_reads) close_semaphore(*count_reads);
  if (NULL != *data_updated) close_semaphore(*data_updated);
  if (NULL != *input_read) close_semaphore(*input_read);
  if (NULL != *input_updated) close_semaphore(*input_updated);

  size_t shm_size = (size_t)sysconf(_SC_PAGESIZE);
  if (NULL != *history) detach_shm_segment(*history, shm_size);
  if (NULL != *users) detach_shm_segment(*users, shm_size);
  if (NULL != *msg) detach_shm_segment(*msg, shm_size);

  destroy_windows(*ui);
}
