#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

void signal_handler(int signal_number, const siginfo_t *info, void *args) {
  const ucontext_t *context = (void *)
      args;  // контекст выполнения процесса на момент возникновения сигнала:
             // значения регистров, указатель стека, маска сигналов и т. д.
             // Согласно ману sigaction, оно зачастую не нужно. Некоторые
             // программы используют эту информацию для отображения расширенной
             // диагностики падения, или для попытки восстановления работы
             // (перепрыгивания через инструкцию, вызвавшую срабатывание
             // сигнала), или для восстановления маски сигналов через
             // context->uc_sigmask.
             // Согласно ману getcontext, функции, работающие с этой структурой,
             // удалили в POSIX.1-2008 и рекомендуют использовать POSIX потоки.
             // Короче, наличие этой структуры - это атавизм.

  if (SI_USER == info->si_code) {
    printf("Получен сигнал %s от %d\n", strsignal(signal_number), info->si_pid);
  } else {
    printf("Получен сигнал %s\n", strsignal(signal_number));
  }
  if (NULL != context && NULL != context->uc_link) {
    printf("Указатель на следующую структуру контекста %p\n", context->uc_link);
  }
}
