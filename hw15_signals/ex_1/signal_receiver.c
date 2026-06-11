#include "signal_receiver.h"

int main(void) {
  int err = 0;
  struct sigaction handler;
  sigset_t signal_mask;

  if (-1 == sigemptyset(&signal_mask) ||
      -1 == sigaddset(&signal_mask, SIGUSR1)) {
    err = errno;
    perror("sigemptyset or sigaddset");
  } else {
    handler.sa_mask = signal_mask;
    handler.sa_sigaction = signal_handler;
    handler.sa_flags = SA_SIGINFO;
  }

  if (0 == err && 0 > (err = sigaction(SIGUSR1, &handler, NULL))) {
    perror("sigaction");
  }

  printf("Наш pid %d\n", getpid());

  if (0 == err) {
    while (1) {
      sleep(1);
    }
  }

  return err;
}
