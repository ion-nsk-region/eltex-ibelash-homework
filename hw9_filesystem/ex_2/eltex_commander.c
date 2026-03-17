#include "eltex_commander.h"

int main(void) {
  int ret = 0, button_pressed = 0, left_nfiles, right_nfiles, active_nfiles;
  WINDOW *left_panel, *right_panel, *left_content, *right_content,
      *active_panel, *active_content;
  struct dirent **left_list = NULL, **right_list = NULL, **active_list = NULL;
  char path_buffer[PATH_MAX];

  ret = initialize_terminal();
  if (0 > ret) return ret;

  ret = create_panels(stdscr, &left_panel, &right_panel, &left_content,
                      &right_content);
  if (0 > ret) return ret;
  active_panel = left_panel;

  sprintf(path_buffer, "./");
  const char *left_path = path_buffer;
  if (0 != list_dir(left_path, &left_list, &left_nfiles)) {
    return -1;
  }

  const char *right_path = getenv("HOME");
  if (0 != list_dir(right_path, &right_list, &right_nfiles)) {
    return -2;
  }
  // исходная отрисовка
  resize_panels(left_panel, left_content, right_panel, right_content);
  print_dir(left_content, left_list, left_nfiles);
  print_dir(right_content, right_list, right_nfiles);

  do {
    // Собственно вывод на экран
    wnoutrefresh(stdscr);
    wnoutrefresh(left_content);
    wnoutrefresh(left_panel);
    wnoutrefresh(right_panel);
    wnoutrefresh(right_content);
    doupdate();

    button_pressed = getch();
    switch (button_pressed) {
      case KEY_RESIZE:
        resize_panels(left_panel, left_content, right_panel, right_content);
        print_dir(left_content, left_list, left_nfiles);
        print_dir(right_content, right_list, right_nfiles);
        break;
      case '\t':
        // переключаемся между панелями
        if (active_panel == left_panel) {
          active_panel = right_panel;
          active_content = right_content;
          active_list = right_list;
          active_nfiles = right_nfiles;
        } else if (active_panel == right_panel) {
          active_panel = left_panel;
          active_content = left_content;
          active_list = left_list;
          active_nfiles = left_nfiles;
        }
        print_dir(active_content, active_list, active_nfiles);
        break;
      case KEY_ENTER:
        // открываем директорию или файл

        break;
      default:
        // Обработка случайных нажатий
    }
  } while ('q' != button_pressed);

  ret = cleanup(left_panel, right_panel, left_content, right_content, left_list,
                left_nfiles, right_list, right_nfiles);
  return ret;
}
