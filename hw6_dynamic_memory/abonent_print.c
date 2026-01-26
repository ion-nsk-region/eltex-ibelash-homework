#include "abonent_dir.h"

void abonent_print(struct Abonent abonent) {
  // Позиции колонок захардкодил.
  // Иначе мультибайтные символы отображаются со смещением.
  printf("\033[5G%s\033[16G%s\033[27G%s\n", abonent.name, abonent.second_name,
         abonent.tel);
}
