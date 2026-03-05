#include "eltex_commander.h"

int main() {
  int ret = 0, button_pressed;
  WINDOW *left_panel, *right_panel;

  ret = initialize_terminal();
  if (0 > ret) return ret;

  ret = create_panels(stdscr, &left_panel, &right_panel);
  if (0 > ret) return ret;

  resize_panels(left_panel, right_panel);  // изначальная отрисовка

  do {
    button_pressed = getch();
    switch (button_pressed) {
      case KEY_RESIZE:
        resize_panels(left_panel, right_panel);
        break;
      case '\t':
        // переключаемся между панелями
        break;
      case KEY_ENTER:
        // открываем директорию или файл
         
        break;
      default:
        // Обработка случайных нажатий
    }

    // Собственно вывод на экран
    refresh();
  } while ('q' != button_pressed);

  ret = cleanup(left_panel, right_panel);
  return ret;
}
