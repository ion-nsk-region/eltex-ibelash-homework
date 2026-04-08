#include "ex_1.h"

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
