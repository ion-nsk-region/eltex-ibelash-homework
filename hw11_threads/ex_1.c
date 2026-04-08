#include "ex_1.h"

int main(void) {
  pthread_t loader_tid, customers_tid[N_CUSTOMERS];
  struct shop our_shop;
  printf("Создаём мютексы.\n");
  for (int i = 0; i < N_STANDS; i++) {
    pthread_mutex_init(&our_shop.stand_occupation[i], NULL);
  }

  init_stands(our_shop.shop_stand, N_STANDS, GOODS_MIN, GOODS_MAX);
  spawn_loader(&our_shop, &loader_tid);
  spawn_customers(&our_shop, customers_tid);
  work_till_last_customer(customers_tid);
  set_off_loader(loader_tid);

  printf("Уничтожаем мютексы.\n");
  for (int i = 0; i < N_STANDS; i++) {
    pthread_mutex_destroy(&our_shop.stand_occupation[i]);
  }

  printf("Выходим.\n");

  return 0;
}
