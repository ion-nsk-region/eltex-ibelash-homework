#include "abonent_dir.h"

void clear_dir(struct Directory *dir) {
  int res, dir_size = dir->size;

  for (int i = 0; i < dir_size; i++) {
    res = abonent_del(dir, dir->tail);
    if (0 != res) {
      printf(
          "Произошла ошибка во время удаления."
          "Код ошибки: %d\n",
          res);
    }
  }
}
