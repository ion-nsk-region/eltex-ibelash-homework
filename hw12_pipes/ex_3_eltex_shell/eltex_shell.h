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

int close_pipe_end(int pipe_end);
int configure_child_channels(int *exec_pipe_in, int *exec_pipe_out);
int create_pipe(int **exec_pipe);
int create_pipes(int ***ptr_pipes, int n_pipes);
int elt_cd(char **args);
int input(char user_input[BUFSIZ], int *n_pipes, int *n_words);
int parse_multiple_commands(char *input, char **arguments);
int parse_single_command(char *input, char **arguments);
int run_executable(char **arguments, int *exec_err);
int spawn_children(char **all_args, int n_pipes, int **exec_err,
                   int **exec_pipe, int n_words);
//int wait_and_handle_errors(pid_t executable_pid, int *exec_err);
int wait_and_handle_errors(pid_t executable_pid);

#endif // ELTEX_SHELL_H
