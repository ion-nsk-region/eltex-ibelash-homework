#include <errno.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define N_STANDS 5
#define GOODS_MIN 900
#define GOODS_MAX 1100
#define CUSTOMER_NEED_MIN 9900
#define CUSTOMER_NEED_MAX 10100
#define N_CUSTOMERS 3
#define CUSTOMER_SLEEP 2
#define LOADER_CARGO 200
#define LOADER_SLEEP 1

struct shop {
  unsigned int shop_stand[N_STANDS];
  pthread_mutex_t stand_occupation[N_STANDS];
};

void init_stands(unsigned int *shop_stand, unsigned int n_stands,
                 unsigned int goods_min, unsigned int goods_max);
void *loader(void *arg);
void spawn_loader(struct shop *our_shop, pthread_t *loader_tid);
void set_off_loader(pthread_t loader_tid);

int main(void) {
  pthread_t loader_tid;
  struct shop our_shop;
  printf("Создаём мютексы.\n");
  for (int i = 0; i < N_STANDS; i++) {
    pthread_mutex_init(&our_shop.stand_occupation[i], NULL);
  }

  init_stands(our_shop.shop_stand, N_STANDS, GOODS_MIN, GOODS_MAX);

  spawn_loader(&our_shop, &loader_tid);
  sleep(5);
  /*
  printf("Покупатели заходят в магазин.\n");
  spawn_customers(&shop_stand);

  work_till_last_customer();
  printf("Все покупатели закупились.\n");
  */

  set_off_loader(loader_tid);

  printf("Уничтожаем мютексы.\n");
  for (int i = 0; i < N_STANDS; i++) {
    pthread_mutex_destroy(&our_shop.stand_occupation[i]);
  }

  printf("Выходим.\n");

  return 0;
}

void init_stands(unsigned int *shop_stand, unsigned int n_stands,
                 unsigned int goods_min, unsigned int goods_max) {
  srand(time(NULL));

  *shop_stand = goods_min + rand() % (goods_max - goods_min + 1);
  printf("Исходное состояние ларьков:\n%u", *shop_stand);
  for (unsigned int *p = (shop_stand + 1); p - shop_stand < n_stands; p++) {
    *p = goods_min + rand() % (goods_max - goods_min + 1);
    printf(" %u", *p);
  }
  printf("\n");
}

void spawn_loader(struct shop *our_shop, pthread_t *loader_tid) {
  printf("Погрузчик выходит на работу.\n");
  pthread_create(loader_tid, NULL, loader, our_shop);
}

void *loader(void *arg) {
  struct shop *our_shop = arg;

  while (1) {
    unsigned int stand_num;
    int ret;
    stand_num = rand() % N_STANDS;
    ret = pthread_mutex_trylock(&our_shop->stand_occupation[stand_num]);
    if (0 == ret) {
      printf("Погрузчик зашёл в ларёк %u.\n", stand_num);
      our_shop->shop_stand[stand_num] =
          our_shop->shop_stand[stand_num] + LOADER_CARGO;
      printf("\tВ ларке %u стало %u товара.\n", stand_num,
             our_shop->shop_stand[stand_num]);
      pthread_mutex_unlock(&our_shop->stand_occupation[stand_num]);
      sleep(LOADER_SLEEP);  // точка отмены потока
    } else if (EBUSY == ret) {
      // ларёк занят, идём в другой
      printf("Погрузчик пытался зайти в ларёк %u, но там уже кто-то есть.\n",
             stand_num);
      // sleep(LOADER_SLEEP); // в задании как-то не уточнено, должен ли он
      // спать при неудачной попытке, или нет.
    } else {
      printf("Ошибка при попытке заблокировать мютекс: %d", ret);
    }
  }
  return 0;
}

void set_off_loader(pthread_t loader_tid) {
  int ret;

  printf("Отпускаем погрузчика домой.\n");
  ret = pthread_cancel(loader_tid);
  if (0 == ret) {
    printf("Погрузчику сообщили, что работы больше нет.\n");
  } else {
    printf("Не получилось сообщить погрузчику. См. подробности в stderr\n");
    errno = ret;
    perror("pthread_cancel");
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
        "Грузчик! Грузчик! Парень работящий - берёт, кладёт и тащит.\n");
    // падаем?
  }
}
