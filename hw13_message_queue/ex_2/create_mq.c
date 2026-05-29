#include "mq_chat.h"

int create_mq(char *mq_name, int *mq_id) {
  int err = 0;
  key_t key;

  if (NULL != mq_name) {
    errno = 0;
    if (-1 == (key = ftok(mq_name, PROJ_ID))) {
            perror("ftok");
            err = -1;
    } else {
    mode_t mq_perm = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP;
    int mq_flags = mq_perm | IPC_CREAT | IPC_EXCL;
    errno = 0;
    *mq_id = msgget(key, mq_flags);
    }
  }

  if (0 == err && -1 == *mq_id && EEXIST == errno) {
    fprintf(stderr, "Предупреждение: очередь уже существует.\n");
    // проверяем что очередь пуста и опустошаем при необходимости
    if (0 == (err = clear_mq(mq_name))) {
      errno = 0;
      *mq_id = msgget(key, 0);
      fprintf(stderr, "Очередь очищена и открыта для работы.\n");
    } else {
      fprintf(stderr,
              "Ошибка: не удалось очистить существующую очередь.\n"
              "Перезагрузите компьютер чтобы удалить эту очередь.\n");
    }
  } else if (-1 == *mq_id) {
    perror("msgget");
    err = -1;
  }

  return err;
}
