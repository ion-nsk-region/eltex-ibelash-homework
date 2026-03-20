#include "eltex_commander.h"

int cleanup(WINDOW *left_panel, WINDOW *right_panel, WINDOW *left_content,
            WINDOW *right_content, struct dirent **left_list, int left_nfiles,
            struct dirent **right_list, int right_nfiles) {
  int ret = 0;
  if (!cleanup_window(left_content) || !cleanup_window(left_panel) ||
      !cleanup_window(right_content) || !cleanup_window(right_panel)) {
    fprintf(stderr,
            "Не удалось освободить память выделенную для окон.\n"
            "Рекомендуем перезапустить терминал.\n");
    ret += -1;
  }
  if (ERR == endwin()) {
    fprintf(stderr,
            "Не удалось вернуть настройки терминала в исходное состояние.\n"
            "Рекомендуем перезапустить терминал.\n");
    ret += -1;
  }
  if (!cleanup_namelist(left_list, left_nfiles) ||
      !cleanup_namelist(right_list, right_nfiles)) {
    fprintf(stderr,
            "Не удалось освободить память выделенную для списков файлов.\n"
            "Рекомендуем перезапустить терминал.\n");
    ret += -1;
  }

  return ret;
}
