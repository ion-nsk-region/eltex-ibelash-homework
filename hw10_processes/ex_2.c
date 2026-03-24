#include <errno.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

void process1(pid_t *process3_pid, pid_t *process4_pid);
void process2(pid_t *process5_pid);

int main(void) {
  pid_t process1_pid, process2_pid, process3_pid, process4_pid, process5_pid,
      child_pid = 0;
  int process_status;

  // запускаем первый процесс
  errno = 0;
  process1_pid = fork();
  if (-1 == process1_pid) {
    perror("Process1 fork");
  } else if (0 == process1_pid) {
    process1(&process3_pid, &process4_pid);
  }
  if (0 < process1_pid || -1 == process1_pid) {
    printf(
        "Main: Оби-Ван никогда не рассказывал, что случилось с твоим отцом.\n");

    // запускаем второй процесс
    errno = 0;
    process2_pid = fork();
    if (-1 == process2_pid) {
      perror("Process2 fork");
    } else if (0 == process2_pid) {
      process2(&process5_pid);
    }
  }

  // обрабатываем выход из дочерних процессов
  do {
    errno = 0;
    if (WIFEXITED(process_status) && 0 != child_pid) {
      if (child_pid == process1_pid) {
        printf(
            "Main: Нет, я - твой %d. С криком \"Ааааааа\" Process1 был "
            "завершён со статусом %d.\n",
            getpid(), process_status);
      } else if (child_pid == process2_pid) {
        printf("Main: Process2 завершён со статусом %d.\n", process_status);
      } else if (child_pid == process3_pid) {
        printf("Process1: Process3 завершён со статусом %d.\n", process_status);
      } else if (child_pid == process4_pid) {
        printf("Process1: Process4 завершён со статусом %d.\n", process_status);
      } else if (child_pid == process5_pid) {
        printf("Process2: Process5 завершён со статусом %d.\n", process_status);
      } else if (child_pid == -1) {
        perror("Processes wait");
      } else {
        printf("Мы не должны были тут оказаться. PID %d PPID %d\n", getpid(),
               getppid());
      }
    }
  } while (0 < (child_pid = wait(&process_status)));
  return 0;
}

void process1(pid_t *process3_pid, pid_t *process4_pid) {
  printf(
      "Process1: Он рассказал мне достаточно. "
      "Он сказал мне (%d), что ты убил моего %d.\n",
      getpid(), getppid());
  errno = 0;
  *process3_pid = fork();
  if (-1 == *process3_pid) {
    perror("Process3 fork");
  } else if (0 == *process3_pid) {
    printf("Process3: PID %d, PPID %d\n", getpid(), getppid());
  }
  if (0 < *process3_pid || -1 == *process3_pid) {
    errno = 0;
    *process4_pid = fork();
    if (-1 == *process4_pid) {
      perror("Process4 fork");
    } else if (0 == *process4_pid) {
      printf("Process4: PID %d, PPID %d\n", getpid(), getppid());
    }
  }
}

void process2(pid_t *process5_pid) {
  printf("Process2: PID %d, PPID %d\n", getpid(), getppid());
  errno = 0;
  *process5_pid = fork();
  if (-1 == *process5_pid) {
    perror("Process5 fork");
  } else if (0 == *process5_pid) {
    printf("Process5: PID %d, PPID %d\n", getpid(), getppid());
  }
}
