#include "shm_chat.h"

int init_chat(void **shm_addr, sem_t **sem4_input_updated,
              sem_t **sem4_input_read, struct user **users,
              struct chat_msg **history, sem_t **sem4_data_updated,
              sem_t **sem4_count_reads) {
  size_t page_size = (size_t)sysconf(_SC_PAGESIZE);

  // input
  *shm_addr = create_and_attach_shm_segment(SHM_INPUT, page_size);
  if ((void *)-1 == *shm_addr) {
    goto err_exit;
  } else if ((void *)-2 == *shm_addr) {
    goto destroy_shm_input;
  }

  // users
  *users = create_and_attach_shm_segment(SHM_USERS, page_size);
  if ((void *)-1 == *users) {
    goto detach_shm_input;
  } else if ((void *)-2 == *users) {
    goto destroy_shm_users;
  }
  
  // history
  *history = create_and_attach_shm_segment(SHM_HISTORY, page_size);
  if ((void *)-1 == *history) {
    goto detach_shm_users;
  } else if ((void *)-2 == *history) {
    goto destroy_shm_history;
  }

  // Семафоры
  errno = 0;
  *sem4_input_updated = sem_open(SEM4_INPUT_UPDATED, O_CREAT, perms, 0);
  if (SEM_FAILED == *sem4_input_updated) {
    perror("sem_open");
    goto detach_shm_history;
  }

  errno = 0;
  *sem4_input_read = sem_open(SEM4_INPUT_READ, O_CREAT, perms, 0);
  if (SEM_FAILED == *sem4_input_read) {
    perror("sem_open");
    goto destroy_sem4_input_updated;
  }

  errno = 0;
  *sem4_data_updated = sem_open(SEM4_DATA_UPDATED, O_CREAT, perms, 0);
  if (SEM_FAILED == *sem4_data_updated) {
    perror("sem_open");
    goto destroy_sem4_input_read;
  }

  errno = 0;
  *sem4_count_reads = sem_open(SEM4_COUNT_READS, O_CREAT, perms, 0);
  if (SEM_FAILED == *sem4_count_reads) {
    perror("sem_open");
    goto destroy_sem4_data_updated;
  }


  return 0;

// очистка ресурсов в случае ошибки

destroy_sem4_data_updated:
  destroy_semaphore(*sem4_data_updated, SEM4_DATA_UPDATED);

destroy_sem4_input_read:
  destroy_semaphore(*sem4_input_read, SEM4_INPUT_READ);

destroy_sem4_input_updated:
  destroy_semaphore(*sem4_input_updated, SEM4_INPUT_UPDATED);

detach_shm_history:
  detach_shm_segment(*history, page_size);
destroy_shm_history:
  destroy_shm_segment(SHM_HISTORY);

detach_shm_users:
  detach_shm_segment(*users, page_size);
destroy_shm_users:
  destroy_shm_segment(SHM_USERS);

detach_shm_input:
  detach_shm_segment(*shm_addr, page_size);
destroy_shm_input:
  destroy_shm_segment(SHM_INPUT);

err_exit:
  return -1;
}
