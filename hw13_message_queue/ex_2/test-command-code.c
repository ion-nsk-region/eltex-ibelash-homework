#include <stdio.h>

void command_code(char *command);

int main(void) {
    command_code("/");
    command_code("/quit");
    command_code("/join");
    command_code("/nick");
    command_code("/disconnected");
    return 0;
}

void command_code(char *command) {
  int sum = 0;
  char *p = command;
  while('\0' != *p) {
    sum += *p;
    p++;
  }

  printf("%s: %d\n", command, sum);
}
