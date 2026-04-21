#include "eltex_shell.h"

int parse_single_command(char *input, char **arguments) {
  char **p = arguments;
  char *token = strtok(input, " ");

  if (NULL == token) return -1;

  while (NULL != token) {
    *p = token;
    p++;
    token = strtok(NULL, " ");
  }
  *p = NULL;  // последний аргумент должен быть NULL для execvp

  return p - arguments;  // n_words
}
