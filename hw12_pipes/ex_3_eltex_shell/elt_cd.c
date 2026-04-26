#include "eltex_shell.h"

int elt_cd(char **args) {

  int err = 0;
  if (NULL == args[1] || 0 == strcmp("~", args[1])) {
    args[1] = getenv("HOME");
  }
  errno = 0;
  if (0 != chdir(args[1])) {
    perror("cd");
    err = -1;
  }

  return err;
}
