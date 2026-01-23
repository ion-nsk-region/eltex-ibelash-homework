#include "abonent_dir.h"

void abonent_del(struct Abonent *the_abonent) {
  int n = FIELD_SIZE - 1;
  for (int i = 0; i < n; i++) {
    the_abonent->name[i] = '0';
    the_abonent->second_name[i] = '0';
    the_abonent->tel[i] = '0';
  }
  the_abonent->name[n] = '\0';
  the_abonent->second_name[n] = '\0';
  the_abonent->tel[n] = '\0';
}
