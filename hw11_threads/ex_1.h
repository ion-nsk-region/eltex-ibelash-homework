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
void *customer(void *arg);
void spawn_customers(struct shop *our_shop,
                     pthread_t customers_tid[N_CUSTOMERS]);
void work_till_last_customer(pthread_t customers_tid[N_CUSTOMERS]);
