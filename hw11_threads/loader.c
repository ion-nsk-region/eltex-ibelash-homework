#include "ex_1.h"

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
      printf("Погрузчик ушёл на склад и вернётся через 1 секунду.\n");
      sleep(LOADER_SLEEP);  // точка отмены потока
      printf("Погрузчик вернулся с товаром.\n");
    } else if (EBUSY == ret) {
      // ларёк занят, идём в другой
      printf("Погрузчик пытался зайти в ларёк %u, но там уже кто-то есть.\n",
             stand_num);
      // sleep(LOADER_SLEEP); // в задании как-то не уточнено, должен ли он
      // спать при неудачной попытке, или нет.
    } else {
      printf(
          "Погрузчик не смог заблокировать мютекс ларька %u. "
          "См. подробности в stderr.",
          stand_num);
      errno = ret;
      perror("pthread_mutex_trylock");
    }
  }
  return (void *)0;
}
