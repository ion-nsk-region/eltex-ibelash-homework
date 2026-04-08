#include "ex_1.h"

void spawn_loader(struct shop *our_shop, pthread_t *loader_tid) {
  printf("Погрузчик выходит на работу.\n");
  pthread_create(loader_tid, NULL, loader, our_shop);
}
