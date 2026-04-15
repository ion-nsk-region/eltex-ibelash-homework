#include "eltex_shell.h"

int parse_input(char user_input[BUFSIZ], int user_input_length,
                char **arguments) {
  if (0 == user_input_length) {
    return 0;
  }
  char **p = arguments;
  char *token = strtok(user_input, " ");

  while (NULL != token) {
    *p = token;
    p++;
    token = strtok(NULL, " ");
  }
  *p = NULL;  // последний аргумент должен быть NULL для execvp

  return p - arguments;
}
