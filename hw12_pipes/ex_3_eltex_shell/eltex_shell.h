#ifndef ELTEX_SHELL_H
#define ELTEX_SHELL_H

#include <errno.h>
#include <fcntl.h>
#include <limits.h>
#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int elt_cd(char **args);
int input(char user_input[BUFSIZ], int *user_input_length);
int parse_input(char user_input[BUFSIZ], int user_input_length,
                char **arguments);
int pipe4exec_err(int *exec_err);
int run_executable(char **arguments, int *exec_err);
int wait_and_handle_errors(pid_t executable_pid, int *exec_err);

#endif // ELTEX_SHELL_H
