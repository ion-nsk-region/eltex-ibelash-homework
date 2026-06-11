#ifndef SIGNAL_RECEIVER_H
#define SIGNAL_RECEIVER_H

#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void signal_handler(int signal_number, siginfo_t *info, void *args);

#endif  // SIGNAL_RECEIVER_H
