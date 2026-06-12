#include "signal_receiver.h"

int main(void) {
  int err = 0, signal_number = 0;
  sigset_t signal_mask;

  if (-1 == sigemptyset(&signal_mask) ||
      -1 == sigaddset(&signal_mask, SIGUSR1)) {
    err = errno;
    perror("sigemptyset or sigaddset");
  }

  if (0 == err && 0 > (err = sigprocmask(SIG_BLOCK, &signal_mask, NULL))) {
    perror("sigprocmask");
  }

  printf("Наш pid %d\n", getpid());

  if (0 == err) {
    while (1) {
      sigwait(&signal_mask, &signal_number);
      printf("Получен сигнал %s\n", strsignal(signal_number));
    }
  }

  return err;
}
