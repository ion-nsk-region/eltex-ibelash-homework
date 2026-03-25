#include <errno.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void) {
  pid_t child_pid;
  int status;

  errno = 0;
  child_pid = fork();
  if (-1 == child_pid) {
    perror("fork");
  } else if (0 == child_pid) {
    printf("CHILD: PID: %d PPID: %d\n", getpid(), getppid());
  } else {
    printf("PARENT: PID: %d PPID: %d\n", getpid(), getppid());
    errno = 0;
    if (child_pid == wait(&status) && WIFEXITED(status)) {
      printf("PARENT: Child exited with status %d\n", WEXITSTATUS(status));
    } else {
      perror("wait");
    }
  }

  return 0;
}
