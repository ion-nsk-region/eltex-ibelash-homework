#include "ex_1.h"

void set_off_loader(pthread_t loader_tid) {
  printf("Отпускаем погрузчика домой.\n");
  int ret = pthread_cancel(loader_tid);
  if (0 == ret) {
    printf("Погрузчику сообщили, что работы больше нет.\n");
  } else {
    errno = ret;
    perror("pthread_cancel");
    printf(
        "Не получилось отправить погрузчика домой. "
        "См. подробности в stderr\n");
    // падаем?
  }

  void *result;
  ret = pthread_join(loader_tid, &result);
  if (0 != ret) {
    errno = ret;
    perror("pthread_join");
  }

  if (PTHREAD_CANCELED == result) {
    printf("Погрузчик ушёл домой.\n");
  } else {
    printf(
        "Погрузчик всё ещё работает тихонько напевая:\n"
        "Грузчик! Грузчик! Парень работящий - прёт, кладёт и тащит.\n");
    // падаем?
  }
}
