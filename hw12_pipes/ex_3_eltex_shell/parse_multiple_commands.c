#include "eltex_shell.h"

int parse_multiple_commands(char *input, char **arguments) {
  char **p = arguments;
  char *token = strtok(input, "|");

  if (NULL == token) return -1;

  while (NULL != token) {
    *p = token;
    p++;
    token = strtok(NULL, "|");
  }
  //  *p = NULL;

  return p - arguments;  // n_commands
}
