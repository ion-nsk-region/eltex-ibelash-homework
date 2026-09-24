
#include "shm_chat.h"

int init_chat(int *shm_fd, void **shm_addr, sem_t *sem4_id) {
  int perms = 0600;
  int flags = O_CREAT | O_RDWR;
  unsigned long page_size = sysconf(_SC_PAGESIZE);

  errno = 0;
  *shm_fd = shm_open(SHM_FILENAME, flags, perms);
  if (-1 == *shm_fd) {
    perror("shm_open");
    goto err_exit;
  }

  if (-1 == ftruncate(*shm_fd, (off_t)page_size)) {
    perror("ftruncate");
    goto destroy_shm_segment;
  }

  *shm_addr = attach_shm_segment(*shm_fd, (size_t)page_size);
  if (MAP_FAILED == *shm_addr) {
    goto destroy_shm_segment;
  }

  errno = 0;
  *sem4_id = sem_open(SHM_FILENAME, O_CREAT, perms, 0);
  if (-1 == *sem4_id) {
    perror("sem_open");
    goto detach_shm_segment;
  }

  return 0;

detach_shm_segment:
  detach_shm_segment(*shm_addr);

destroy_shm_segment:
  destroy_shm_segment(*shm_fd);

err_exit:
  return -1;
}
