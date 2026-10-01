
#include "shm_chat.h"

int init_chat(void **shm_addr, sem_t *sem4_server, sem_t *sem4_client) {
  int perms = 0600;
  int flags = O_CREAT | O_RDWR;
  unsigned long page_size = sysconf(_SC_PAGESIZE);

  errno = 0;
  int shm_fd = shm_open(SHM_FILENAME, flags, perms);
  if (-1 == shm_fd) {
    perror("shm_open");
    goto err_exit;
  }

  if (-1 == ftruncate(shm_fd, (off_t)page_size)) {
    perror("ftruncate");
    goto destroy_shm_segment;
  }

  *shm_addr = attach_shm_segment(shm_fd, (size_t)page_size);
  if (MAP_FAILED == *shm_addr) {
    goto destroy_shm_segment;
  }

  errno = 0;
  sem4_server = sem_open(SEM4_SERVER, O_CREAT, perms, 0);
  if (SEM_FAILED == sem4_server) {
    perror("sem_open");
    goto detach_shm_segment;
  }

  errno = 0;
  sem4_client = sem_open(SEM4_CLIENT, O_CREAT, perms, 0);
  if (SEM_FAILED == sem4_client) {
    perror("sem_open");
    goto destroy_sem4_server;
  }

  return 0;

destroy_sem4_server:
  destroy_semaphore(sem4_server, SEM4_SERVER);

detach_shm_segment:
  detach_shm_segment(*shm_addr, (size_t)page_size);

destroy_shm_segment:
  destroy_shm_segment(SHM_FILENAME);

err_exit:
  return -1;
}
