#include "shm_chat.h"

void *init_chat(void) {
  key_t key = ftok(SERVER_FILENAME, PROJ_ID);
  int perms = 0600;
  int flags = IPC_CREAT | perms;

  errno = 0;
  int shm_id = shmget(key, PAGE_SIZE, flags);
  if (-1 == shm_id) {
    perror("shmget");
    goto err_exit;
  }

  void *shm_addr = attach_shm_segment(shm_id);
  if ((void *)-1 == shm_addr) {
    goto destroy_shm_segment;
  }

  errno = 0;
  int sem4_id = semget(key, 1, flags);
  if (-1 == sem4_id) {
    perror("semget");
    goto detach_shm_segment;
  }

  // по идее, следующий код не нужен на Linux, так как семафоры там сразу
  // инициализируются нулём. Но может понадобиться на других ОСях.
  union semun arg;
  arg.val = 0;
  errno = 0;
  int err = semctl(sem4_id, 0, SETVAL, arg);
  if (-1 == err) {
    perror("init_chat > semctl");
    goto destroy_semaphore;
  }

  return shm_addr;

destroy_semaphore:
  destroy_semaphore(sem4_id);

detach_shm_segment:
  detach_shm_segment(shm_addr);

destroy_shm_segment:
  destroy_shm_segment(shm_id);

err_exit:
  return NULL;
}
