#include "server.h"

int init_chat(void **shm_addr, sem_t **sem4_input_updated,
              sem_t **sem4_input_read, struct user **users,
              struct chat_history **history, sem_t **sem4_data_updated,
              sem_t **sem4_count_reads, sem_t **sem4_next_turn) {
  size_t shm_size = (size_t)sysconf(_SC_PAGESIZE);
  int shm_flags = O_CREAT | O_RDWR;

  // input
  *shm_addr = attach_shm_segment(SHM_INPUT, shm_size, shm_flags);
  if ((void *)-1 == *shm_addr) {
    goto err_exit;
  } else if ((void *)-2 == *shm_addr) {
    goto destroy_shm_input;
  }

  // users
  *users = attach_shm_segment(SHM_USERS, shm_size, shm_flags);
  if ((void *)-1 == *users) {
    goto detach_shm_input;
  } else if ((void *)-2 == *users) {
    goto destroy_shm_users;
  }

  // history
  *history = attach_shm_segment(SHM_HISTORY, shm_size, shm_flags);
  if ((void *)-1 == *history) {
    goto detach_shm_users;
  } else if ((void *)-2 == *history) {
    goto destroy_shm_history;
  }

  (*history)->first_msg = 0;
  (*history)->last_msg = 0;
  (*history)->edge_msg = 0;

  // Семафоры
  mode_t perms = 0600;
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
  sem_post(*sem4_input_read);  // взводим семафор чтобы прочитать самое первое
                               // сообщение

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

  errno = 0;
  *sem4_next_turn = sem_open(SEM4_NEXT_TURN, O_CREAT, perms, 0);
  if (SEM_FAILED == *sem4_next_turn) {
    perror("sem_open");
    goto destroy_sem4_count_reads;
  }

  return 0;

  // очистка ресурсов в случае ошибки

destroy_sem4_count_reads:
  destroy_semaphore(*sem4_count_reads, SEM4_COUNT_READS);

destroy_sem4_data_updated:
  destroy_semaphore(*sem4_data_updated, SEM4_DATA_UPDATED);

destroy_sem4_input_read:
  destroy_semaphore(*sem4_input_read, SEM4_INPUT_READ);

destroy_sem4_input_updated:
  destroy_semaphore(*sem4_input_updated, SEM4_INPUT_UPDATED);

detach_shm_history:
  detach_shm_segment(*history, shm_size);
destroy_shm_history:
  destroy_shm_segment(SHM_HISTORY);

detach_shm_users:
  detach_shm_segment(*users, shm_size);
destroy_shm_users:
  destroy_shm_segment(SHM_USERS);

detach_shm_input:
  detach_shm_segment(*shm_addr, shm_size);
destroy_shm_input:
  destroy_shm_segment(SHM_INPUT);

err_exit:
  return -1;
}
