#include "ex_1.h"

void *customer(void *arg) {
  struct shop *our_shop = arg;
  int need =
      rand() % (CUSTOMER_NEED_MAX - CUSTOMER_NEED_MIN) + CUSTOMER_NEED_MIN;
  pthread_t customer_tid = pthread_self();

  do {
    unsigned int stand_num;
    int ret;
    stand_num = rand() % N_STANDS;

    ret = pthread_mutex_trylock(&our_shop->stand_occupation[stand_num]);
    if (0 == ret) {
      printf("Покупатель %lx зашёл в ларёк %u где было %u единиц товара.\n",
             customer_tid, stand_num, our_shop->shop_stand[stand_num]);
      need = need - our_shop->shop_stand[stand_num];
      our_shop->shop_stand[stand_num] = 0;
      pthread_mutex_unlock(&our_shop->stand_occupation[stand_num]);
      printf("\tПокупателю %lx требуется ещё %d единиц товара.\n", customer_tid,
             need);
      printf("\tПокупатель %lx уснул на 2 секунды.\n", customer_tid);
      sleep(CUSTOMER_SLEEP);
      printf("Покупатель %lx проснулся. Его текущая потребность %d.\n",
             customer_tid, need);
    } else if (EBUSY == ret) {
      printf(
          "Покупатель %lx пытался зайти в ларёк %u, но там уже кто-то есть.\n",
          customer_tid, stand_num);
    } else {
      errno = ret;
      perror("pthread_mutex_trylock");
      printf(
          "Покупатель %lx не смог заблокировать мютекс ларька %u. "
          "См. подробности в stderr.",
          customer_tid, stand_num);
    }
  } while (0 < need);

  printf("Покупатель %lx удовлетворил свою потребность.\n", customer_tid);
  return (void *)0;
}
