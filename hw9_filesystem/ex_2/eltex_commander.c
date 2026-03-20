#include "eltex_commander.h"

int main(void) {
  int ret = 0, button_pressed = 0, left_nfiles, right_nfiles, active_nfiles,
      left_select = 1, right_select = 1, active_select;
  WINDOW *left_panel, *right_panel, *left_content, *right_content,
      *active_panel, *active_content;
  struct dirent **left_list = NULL, **right_list = NULL, **active_list = NULL;
  char path_buffer[PATH_MAX];
  char *active_path = NULL, *left_path = NULL, *right_path = NULL;

  ret = initialize_terminal();
  if (0 > ret) return ret;

  ret = create_panels(stdscr, &left_panel, &right_panel, &left_content,
                      &right_content);
  if (0 > ret) return ret;

  // Первоначально открываемые директории: текущая и домашняя
  sprintf(path_buffer, "./");
  left_path = realpath(path_buffer, NULL);
  if (NULL == left_path || 0 != list_dir(left_path, &left_list, &left_nfiles)) {
    fprintf(stderr,
            "Не удалось отобразить содержимое текущей директории. Выходим.");
    return -1;
  }

  right_path = realpath(getenv("HOME"), NULL);
  if (NULL == right_path ||
      0 != list_dir(right_path, &right_list, &right_nfiles)) {
    fprintf(stderr,
            "Не удалось отобразить содержимое домашней директории. Выходим.");
    return -2;
  }

  active_panel = left_panel;
  active_content = left_content;
  switch_data(left_path, left_list, left_nfiles, left_select, &active_path,
              &active_list, &active_nfiles, &active_select);
  // исходная отрисовка
  print_all(left_panel, left_content, left_list, left_nfiles, right_panel,
            right_content, right_list, right_nfiles, active_content,
            active_select);

  status_bar(
      "q - выход, Tab - переключение между панелями, ↑ и ↓ - перемещение по "
      "списку вверх и вниз, Enter - открыть директорию.");

  do {
    // Собственно вывод на экран
    refresh_all(left_panel, left_content, right_panel, right_content);

    button_pressed = getch();
    switch (button_pressed) {
      case KEY_RESIZE:
        print_all(left_panel, left_content, left_list, left_nfiles, right_panel,
                  right_content, right_list, right_nfiles, active_content,
                  active_select);
        break;
      case '\t':
        // переключаемся между панелями
        if (active_panel == left_panel) {
          switch_data(active_path, active_list, active_nfiles, active_select,
                      &left_path, &left_list, &left_nfiles, &left_select);
          switch_data(right_path, right_list, right_nfiles, right_select,
                      &active_path, &active_list, &active_nfiles,
                      &active_select);
          active_panel = right_panel;
          active_content = right_content;
          print_dir(left_content, left_list, left_nfiles, -left_select);
        } else if (active_panel == right_panel) {
          switch_data(active_path, active_list, active_nfiles, active_select,
                      &right_path, &right_list, &right_nfiles, &right_select);
          switch_data(left_path, left_list, left_nfiles, left_select,
                      &active_path, &active_list, &active_nfiles,
                      &active_select);
          active_panel = left_panel;
          active_content = left_content;
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
          char *fallback_path = active_path;
          snprintf(path_buffer, sizeof(path_buffer), "%.3839s/%s", active_path,
                   active_list[active_select]->d_name);
          active_path = realpath(path_buffer, NULL);
          cleanup_namelist(active_list, active_nfiles);
          if (0 == list_dir(active_path, &active_list, &active_nfiles)) {
            active_select = 1;
            free(fallback_path);
          } else {
            status_bar("Не удалось открыть директорию. Подробности в stderr.");
            free(active_path);
            active_path = fallback_path;
            list_dir(active_path, &active_list, &active_nfiles);
          }
          print_dir(active_content, active_list, active_nfiles, active_select);
          if (active_panel == left_panel) {
            switch_data(active_path, active_list, active_nfiles, active_select,
                        &left_path, &left_list, &left_nfiles, &left_select);
          } else if (active_panel == right_panel) {
            switch_data(active_path, active_list, active_nfiles, active_select,
                        &right_path, &right_list, &right_nfiles, &right_select);
          }
        }

        break;
      case 'q':
        ret = cleanup(left_panel, right_panel, left_content, right_content,
                      left_list, left_nfiles, right_list, right_nfiles,
                      left_path, right_path);
        break;
      default:
        // Обработка случайных нажатий
        mvprintw(0, 0, "Pressed %d", button_pressed);
    }
  } while ('q' != button_pressed);

  return ret;
}
