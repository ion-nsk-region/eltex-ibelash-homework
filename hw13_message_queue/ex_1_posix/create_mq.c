#include "mq_chat.h"

int create_mq(char *mq_name, mqd_t *mq_id) {
  int err = 0, mq_flags;

  if (NULL != mq_name) {
    mode_t mq_perm = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP;
    mq_flags = O_WRONLY | O_CLOEXEC | O_CREAT | O_EXCL;
    errno = 0;
    *mq_id = mq_open(mq_name, mq_flags, mq_perm, NULL);
  }

  if (-1 == *mq_id && EEXIST == errno) {
    printf("Предупреждение: очередь уже существует.\n");
    // проверяем что очередь пуста и опустошаем при необходимости
    if (0 == (err = clear_mq(mq_name))) {
      mq_flags = O_WRONLY | O_CLOEXEC;
      errno = 0;
      *mq_id = mq_open(mq_name, mq_flags);
    } else {
      printf(
          "Ошибка: не удалось очистить существующую очередь.\n"
          "Перезагрузите компьютер чтобы удалить эту очередь.\n");
    }
  }

  if (-1 == *mq_id) {
    perror("mq_open");
    err = -1;
  }

  return err;
}
