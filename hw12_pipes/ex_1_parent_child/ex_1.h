#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int create_pipe(int *pipe);
int close_pipe_end(int pipe_end);
ssize_t send_msg_to_pipe(int *my_pipe, char *msg);
void read_msg_from_pipe(int *pipe, char *msg);
int wait4child(pid_t child_pid);
