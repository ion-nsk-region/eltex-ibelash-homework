#include "eltex_commander.h"

void switch_data(char *src_path, struct dirent **src_list, int src_nfiles,
                 int src_select, char **dst_path, struct dirent ***dst_list,
                 int *dst_nfiles, int *dst_select) {
  *dst_select = src_select;
  *dst_path = src_path;
  *dst_list = src_list;
  *dst_nfiles = src_nfiles;
}
