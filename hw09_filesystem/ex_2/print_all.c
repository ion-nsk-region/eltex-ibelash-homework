#include "eltex_commander.h"

void print_all(WINDOW *left_panel, WINDOW *left_content,
               struct dirent **left_list, int left_nfiles, WINDOW *right_panel,
               WINDOW *right_content, struct dirent **right_list,
               int right_nfiles, WINDOW *active_content, int active_select) {
  resize_panels(left_panel, left_content, right_panel, right_content);
  if (active_content == left_content) {
    print_dir(left_content, left_list, left_nfiles, active_select);
    print_dir(right_content, right_list, right_nfiles, -1);
  }
  if (active_content == right_content) {
    print_dir(left_content, left_list, left_nfiles, -1);
    print_dir(right_content, right_list, right_nfiles, active_select);
  }
}
