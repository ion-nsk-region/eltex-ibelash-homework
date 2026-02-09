#include "calc.h"

void unload_plugins(void *func_handles[FUNC_MAX]) {
  char *error;

  for (int i = 1; i < FUNC_MAX; i++) {
    if (NULL != func_handles[i] && 0 != dlclose(func_handles[i])) {
      error = dlerror();
      if (NULL != error) {
        fprintf(stderr, "%s\n", error);
      }
    }
  }
}
