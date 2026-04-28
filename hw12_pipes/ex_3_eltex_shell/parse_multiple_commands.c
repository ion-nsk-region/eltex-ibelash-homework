#include "eltex_shell.h"

int parse_multiple_commands(char *user_input, int n_pipes, int n_words_total,
                            char ****arguments) {
  char *one_command = strtok(user_input, "|");
  if (NULL == one_command) {
    return -1;
  }

  char **buf_cmds = (char **)malloc((n_pipes + 1) * sizeof(char *));
  char **p = buf_cmds;
  while (NULL != one_command) {
    *p = one_command;
    p++;
    one_command = strtok(NULL, "|");
  }

  char **buf_args = (char **)malloc((n_words_total + 1) * sizeof(char *));
  char ***commands = (char ***)malloc((n_pipes + 1) * sizeof(char **));
  char ***ptr = commands;
  for (p = buf_cmds; p - buf_cmds <= n_pipes; p++, ptr++) {
    int n_words = parse_single_command(*p, buf_args);
    *ptr = (char **)malloc((n_words + 1) * sizeof(char *));
    for (char **a = *ptr, **b = buf_args; a - *ptr <= n_words; a++, b++) {
      *a = *b;
    }
  }

  *arguments = commands;

  free(buf_cmds);
  buf_cmds = NULL;
  free(buf_args);
  buf_args = NULL;

  return ptr - commands;  // n_commands
}
