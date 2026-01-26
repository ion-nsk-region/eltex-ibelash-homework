#include "abonent_dir.h"

void clear_dir(struct Directory *dir) {
  for (int i = 0; i <= dir->size; i++) {
    abonent_del(dir, dir->tail);
  }
}
