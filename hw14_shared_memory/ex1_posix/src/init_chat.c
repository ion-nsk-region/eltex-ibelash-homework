
#include "shm_chat.h"

int init_chat(int *shm_fd, void **shm_addr, sem_t *sem4_id) {
  int perms = 0600;
  int flags = O_CREAT | O_RDWR;
  long page_size = sysconf(_SC_PAGESIZE);

  errno = 0;
  *shm_fd = shm_open(SHM_FILENAME, flags, perms);
  if (-1 == *shm_fd) {
    perror("shm_open");
    goto err_exit;
  }

  if (-1 == ftruncate(*shm_fd, page_size)) {
    perror("ftruncate");
    goto destroy_shm_segment;
  }

  *shm_addr = attach_shm_segment(*shm_fd, page_size);
  if ((void *)-1 == *shm_addr) {
    goto destroy_shm_segment;
  }

  errno = 0;
  *sem4_id = sem_open(SHM_FILENAME, flags);
  if (-1 == *sem4_id) {
    perror("semget");
    goto detach_shm_segment;
  }

  // по идее, следующий код не нужен на Linux, так как семафоры там сразу
  // инициализируются нулём. Но может понадобиться на других ОСях.
  union semun arg;
  arg.val = 0;
  errno = 0;
  int err = semctl(*sem4_id, 0, SETVAL, arg);
  if (-1 == err) {
    perror("init_chat > semctl");
    goto destroy_semaphore;
  }

  return 0;

destroy_semaphore:
  destroy_semaphore(*sem4_id);

detach_shm_segment:
  detach_shm_segment(*shm_addr);

destroy_shm_segment:
  destroy_shm_segment(*shm_fd);

err_exit:
  return -1;
}
