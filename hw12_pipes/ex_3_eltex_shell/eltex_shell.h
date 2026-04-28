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

void cleanup(char ****arguments, int ***exec_err, int ***exec_pipe,
             int n_pipes);
int close_pipe_end(int pipe_end);
int configure_child_channels(int *exec_pipe_in, int *exec_pipe_out);
int create_pipe(int **exec_pipe);
int create_pipes(int ***ptr_pipes, int n_pipes);
int elt_cd(char **args);
int input(char user_input[BUFSIZ], int *n_pipes, int *n_words);
int parse_multiple_commands(char *user_input, int n_pipes, int n_words_total,
                            char ****arguments);
int parse_single_command(char *user_input, char **arguments);
int read_exec_err(int *error_pipe);
int run_executable(char **arguments, int *exec_err);
int spawn_children(char ***all_args, int n_pipes, int **exec_err,
                   int **exec_pipe);
int spawn_single_child(char ***arg_ptr, int *exec_pipe_in, int *exec_pipe_out,
                       int **error_pipe_ptr, pid_t *pid_ptr);
int wait4child(pid_t executable_pid);
void wait_all_children(pid_t *executable_pid, int **exec_err, int n_children);

#endif  // ELTEX_SHELL_H
