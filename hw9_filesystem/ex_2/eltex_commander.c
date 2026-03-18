#include "eltex_commander.h"

int main(void) {
  int ret = 0, button_pressed = 0, left_nfiles, right_nfiles, active_nfiles, left_select = 1, right_select = 1, active_select;
  WINDOW *left_panel, *right_panel, *left_content, *right_content,
      *active_panel, *active_content;
  struct dirent **left_list = NULL, **right_list = NULL, **active_list = NULL;
  char path_buffer[PATH_MAX];
  const char *active_path, *left_path, *right_path;

  ret = initialize_terminal();
  if (0 > ret) return ret;

  ret = create_panels(stdscr, &left_panel, &right_panel, &left_content,
                      &right_content);
  if (0 > ret) return ret;

  // Первоначально открываемые директории: текущая и домашняя
  sprintf(path_buffer, "./");
  left_path = path_buffer;
  if (0 != list_dir(left_path, &left_list, &left_nfiles)) {
    return -1;
  }

  right_path = getenv("HOME");
  if (0 != list_dir(right_path, &right_list, &right_nfiles)) {
    return -2;
  }

  active_panel = left_panel;
  active_content = left_content;
  active_select = left_select;
  active_list = left_list;
  active_nfiles = left_nfiles;
  active_path = left_path;
  // исходная отрисовка
  print_all(left_panel, left_content, left_list, left_nfiles, right_panel,
            right_content, right_list, right_nfiles, active_content, active_select);

  do {
    // Собственно вывод на экран
    // debug(left_panel, left_content, right_panel, right_content, active_select);
    refresh_all(left_panel, left_content, right_panel, right_content);

    button_pressed = getch();
    switch (button_pressed) {
      case KEY_RESIZE:
        print_all(left_panel, left_content, left_list, left_nfiles, right_panel,
                  right_content, right_list, right_nfiles, active_content, active_select);
        break;
      case '\t':
        // переключаемся между панелями
        if (active_panel == left_panel) {
          left_select = active_select;
          left_path = active_path;
          active_path = right_path;
          active_panel = right_panel;
          active_content = right_content;
          active_list = right_list;
          active_nfiles = right_nfiles;
          active_select = right_select;
          print_dir(left_content, left_list, left_nfiles, -left_select);
        } else if (active_panel == right_panel) {
          right_select = active_select;
          right_path = active_path;
          active_path = left_path;
          active_panel = left_panel;
          active_content = left_content;
          active_list = left_list;
          active_nfiles = left_nfiles;
          active_select = left_select;
          print_dir(right_content, right_list, right_nfiles, -right_select);
        }
        print_dir(active_content, active_list, active_nfiles, active_select);
        break;
      case KEY_DOWN:
        if (active_select < active_nfiles - 1) {
            active_select++;
            print_dir(active_content, active_list, active_nfiles, active_select);
        }
        break;
      case KEY_UP:
        if (active_select > 0) {
            active_select--;
            print_dir(active_content, active_list, active_nfiles, active_select);
        }
        break;
      case '\n':
        // открываем директорию или файл
        unsigned char filetype = active_list[active_select]->d_type;
        if (DT_DIR == filetype) {
            snprintf(path_buffer, sizeof(path_buffer), "%.3839s/%s", active_path, active_list[active_select]->d_name);
          active_path = path_buffer;

          debug(active_path, path_buffer);

          cleanup_namelist(active_list, active_nfiles);
          list_dir(active_path, &active_list, &active_nfiles);
          active_select = 1;
          print_dir(active_content, active_list, active_nfiles, active_select);
        }

        break;
      default:
        // Обработка случайных нажатий
        mvprintw(0, 0, "Pressed %d", button_pressed);
    }
  } while ('q' != button_pressed);

  ret = cleanup(left_panel, right_panel, left_content, right_content, left_list,
                left_nfiles, right_list, right_nfiles);
  return ret;
}
