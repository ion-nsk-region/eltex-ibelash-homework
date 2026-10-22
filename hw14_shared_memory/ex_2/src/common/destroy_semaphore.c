#include "shm_chat.h"

void destroy_semaphore(sem_t *sem4_id, const char *sem4_name) {
  int err = close_semaphore(sem4_id);
  if (-1 == err) {
    fprintf(stderr,
            "Предупреждение: во время закрытия семафора возникла ошибка. "
            "См. подробности в stderr.\n"
            "Пытаемся удалить семафор несмотря на эту ошибку.\n");
  }

  errno = 0;
  err = sem_unlink(sem4_name);
  if (-1 == err) {
    perror("destroy_semaphore > sem_unlink");
  }
}
