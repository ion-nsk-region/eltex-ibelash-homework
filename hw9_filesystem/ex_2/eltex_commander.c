#include "eltex_commander.h"

int main() {
  int ret = 0, button_pressed, left_nfiles, right_nfiles;
  WINDOW *left_panel, *right_panel, *left_content, *right_content;
  struct dirent **left_list = NULL, **right_list = NULL;
  char path_buffer[PATH_MAX];

  ret = initialize_terminal();
  if (0 > ret) return ret;

  ret = create_panels(stdscr, &left_panel, &right_panel, &left_content,
                      &right_content);
  if (0 > ret) return ret;

  sprintf(path_buffer, "./");
  const char *left_path = path_buffer;
  if (0 != list_dir(left_path, left_list, &left_nfiles)) {
    return -1;
  }
  const char *right_path = path_buffer;
  if (0 != list_dir(right_path, right_list, &right_nfiles)) {
    return -2;
  }


  // изначальная отрисовка
  resize_panels(left_panel, right_panel);
  refresh();
  wrefresh(left_panel);
  wrefresh(right_panel);


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
    wrefresh(left_panel);
    wrefresh(right_panel);
  } while ('q' != button_pressed);

  ret = cleanup(left_panel, right_panel, left_content, right_content, left_list, left_nfiles, right_list, right_nfiles);
  return ret;
}
