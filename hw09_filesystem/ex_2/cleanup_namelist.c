#include "eltex_commander.h"

int cleanup_namelist(struct dirent **namelist, int n) {
  if (NULL != namelist) {
    for (int i = 0; i < n; i++) {
      free(namelist[i]);
    }
    free(namelist);
  }
  return 1;
}
