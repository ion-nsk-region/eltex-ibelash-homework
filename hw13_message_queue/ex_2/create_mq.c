#include "mq_chat.h"

int create_mq(char *mq_name, int *mq_id) {
  int err = 0;
  key_t key;
  mode_t mq_perm = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP;

  if (NULL != mq_name) {
    errno = 0;
    if (-1 == (key = ftok(mq_name, PROJ_ID))) {
            perror("ftok");
            err = -1;
    } else {
    int mq_flags = mq_perm | IPC_CREAT | IPC_EXCL;
    errno = 0;
    *mq_id = msgget(key, mq_flags);
    }
  }

  if (0 == err && -1 == *mq_id && EEXIST == errno) {
    fprintf(stderr, "Предупреждение: очередь %s уже существует.\n", mq_name);
    // проверяем что очередь пуста и опустошаем при необходимости
    if (0 == (err = clear_mq(mq_name))) {
      errno = 0;
      *mq_id = msgget(key, mq_perm);
      fprintf(stderr, "Очередь %s очищена и открыта для работы с id %d.\n", mq_name, *mq_id);
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
