#include <dlfcn.h>

#include "calc.h"

void run_operation(void *func_handle, char *func_name) {
  char *error;
  int (*operation)(int, int);
  int a, b, result;

  operation = dlsym(func_handle, func_name);
  error = dlerror();
  if (NULL != error) {
    fprintf(stderr, "%s\n", error);
    return;
  }

  while (0 != calc_input(&a, &b)) {
    printf("Попробуйте снова.\n\n");
  }

  result = (*operation)(a, b);
  printf("%d\n\n", result);
}
