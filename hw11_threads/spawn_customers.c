#include "ex_1.h"

void spawn_customers(struct shop *our_shop,
                     pthread_t customers_tid[N_CUSTOMERS]) {
  printf("Покупатели заходят в магазин.\n");
  for (int i = 0; i < N_CUSTOMERS; i++) {
    pthread_create(&customers_tid[i], NULL, customer, our_shop);
  }
}
