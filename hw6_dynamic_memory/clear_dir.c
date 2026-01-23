#include "abonent_dir.h"

void clear_dir(struct Abonent directory[DIR_SIZE]) {
  for (int i = 0; i < DIR_SIZE; i++) {
    abonent_del(&directory[i]);
  }
}
