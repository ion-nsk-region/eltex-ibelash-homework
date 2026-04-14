#ifndef MYPIPE2_H
#define MYPIPE2_H

#include <errno.h>
#include <fcntl.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

// #define PIPE_PATH "./my_pipe2"
#define PIPE_PATH "/tmp/my_pipe2"

// промежуток времени в секундах между попытками записать или прочитать
// содержимое канала
#define SLEEP_TIME 1  // в секундах

// общее время ожидания подключения другой стороны
#define CONNECTION_TIMEOUT 60  // в секундах

int create_pipe(char *pipe_path);
int delete_pipe(char *pipe_path);
int close_pipe(int pipe_fd);
int send_msg_to_pipe(char *pipe_path, int connection_timeout, char *msg);
int read_msg_from_pipe(char *pipe_path, int conn_timeout, char *msg);
int conn_timer(int connection_timeout, int n_attempts);
int wait4server(char *pipe_path, int conn_timeout, int *pipe_fd);

#endif // MYPIPE2_H
