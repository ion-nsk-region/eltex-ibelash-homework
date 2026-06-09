#include <signal.h>

#include "client_ui.h"

void safe_exit() { endwin(); }

void handle_signal(int sig) {
  safe_exit();
  exit(sig);
}

void restore_terminal(void) {
  atexit(safe_exit);

  //    signal(SIGINT, handle_signal);
  signal(SIGABRT, handle_signal);
  signal(SIGTERM, handle_signal);
  signal(SIGSEGV, handle_signal);
}
