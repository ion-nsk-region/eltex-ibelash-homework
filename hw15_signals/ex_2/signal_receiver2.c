#include "signal_receiver2.h"

int main(void) {
  int err = 0;
  sigset_t signal_mask;

  if (-1 == sigemptyset(&signal_mask) ||
      -1 == sigaddset(&signal_mask, SIGINT)) {
    err = errno;
    perror("sigemptyset or sigaddset");
  }

  // блокируем сигналы
  if (0 == err && 0 > (err = sigprocmask(SIG_BLOCK, &signal_mask, NULL))) {
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
