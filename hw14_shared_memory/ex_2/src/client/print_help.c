#include "client.h"

void print_help(struct ui ui) {
  wmove(ui.history, 0, 0);
  wprintw(ui.history,
          "СПРАВКА\n"
          "  Esc - выйти из чата.\n"
          "  Enter - отправить введённое сообщение.\n"
          "НЕ изменяйте размер терминала, пожалуйста!\n\n");
}
