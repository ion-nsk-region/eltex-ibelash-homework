#include "mq_chat.h"

int connect2mq(char *mq_name, int *mq_id) {
  int err = 0;

  if (NULL != mq_name) {
    errno = 0;
    FILE *f = fopen(mq_name, "r");
    if (NULL == f) {
      err = errno;
      perror("fopen");
      fprintf(stderr,
              "Ошибка: не удалось открыть очередь связанную с файлом %s. "
              "Перейдите в директорию с этим файлом и запустите программу.\n",
              mq_name);
    } else {
      fclose(f);
    }
    key_t key;
    errno = 0;
    if (0 == err && -1 == (key = ftok(mq_name, PROJ_ID))) {
      perror("ftok");
      err = -1;
    } else if (0 == err) {
      int n_attempts = 0;
      do {
        errno = 0;
        *mq_id = msgget(key, 0);
      } while (-1 == *mq_id && ENOENT == errno &&
               ETIME != (err = conn_timer(CONNECTION_TIMEOUT, SLEEP_TIME,
                                          n_attempts++)));
      if (-1 == *mq_id && ETIME != err) {
        perror("msgget");
        err = -1;
      }
    }
  }

  return err;
}
