#include "shm_chat.h"

int init_client(void **shm_addr, sem_t *sem4_server, sem_t *sem4_client) {
  int shm_fd, flags = O_RDWR;
  unsigned long page_size = sysconf(_SC_PAGESIZE);

  errno = 0;
  shm_fd = shm_open(SHM_FILENAME, flags, 0 /* Сервер должен был создать сегмент памяти, поэтому мы не указываем никаких прав */);
  if (-1 == *shm_fd) {
    perror("shm_open");
    goto err_exit;
  }

  *shm_addr = attach_shm_segment(*shm_fd, (size_t)page_size);
  if (MAP_FAILED == *shm_addr) {
    goto err_exit;
  }

  errno = 0;
  sem4_server = sem_open(SEM4_SERVER, 0 /* Сервер должен создать семафор, поэтому мы не указываем никаких флагов */);
  if (SEM_FAILED == sem4_server) {
    perror("sem_open");
    goto detach_shm_segment;
  }

  errno = 0;
  sem4_client = sem_open(SEM4_CLIENT, 0 /* Сервер должен создать семафор, поэтому мы не указываем никаких флагов */);
  if (SEM_FAILED == sem4_client) {
    perror("sem_open");
    goto close_sem4_server;
  }

  return 0;

close_sem4_server:
  close_semaphore(sem4_server);

detach_shm_segment:
  detach_shm_segment(*shm_addr, (size_t)page_size);

err_exit:
  return -1;
}
