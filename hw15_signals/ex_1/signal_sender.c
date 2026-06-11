#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>

int main(void) {
  int err = 0;
  pid_t signal_receiver_pid;

  printf("Наш pid %d\n", getpid());
  printf("Введите pid процесса, которому надо отправить SIGUSR1: ");
  if (1 == scanf("%d", &signal_receiver_pid)) {
    if (-1 == kill(signal_receiver_pid, SIGUSR1)) {
      err = errno;
      perror("kill");
    }
  }

  return err;
}
