#include "ex_1.h"

void work_till_last_customer(pthread_t customers_tid[N_CUSTOMERS]) {
  void *status;
  for (int i = 0; i < N_CUSTOMERS; i++) {
    int ret;
    if (0 == (ret = pthread_join(customers_tid[i], &status))) {
      long int exit_code = (long int)status;
      printf("Покупатель %lx покинул магазин со статусом %ld.\n",
             customers_tid[i], exit_code);
    } else {
      errno = ret;
      perror("pthread_join");
      printf("Покупателю %lx стало плохо. См. подробности в stderr.",
             customers_tid[i]);
      // падаем?
    }
  }
  printf("Все покупатели закупились.\n");
}
