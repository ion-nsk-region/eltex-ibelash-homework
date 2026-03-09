#ifndef ELTEX_COMMANDER_H
#define ELTEX_COMMANDER_H

#include <curses.h>
#include <dirent.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int cleanup(WINDOW *left_panel, WINDOW *right_panel, WINDOW *left_content,
            WINDOW *right_content, struct dirent **left_list, int left_nfiles,
            struct dirent **right_list, int right_nfiles);
int cleanup_window(WINDOW *win);
int cleanup_namelist(struct dirent **namelist, int n);
int create_panels(WINDOW *stdscr, WINDOW **left_panel, WINDOW **right_panel,
                  WINDOW **left_content, WINDOW **right_content);
int initialize_terminal(void);
int list_dir(const char dir_path[PATH_MAX], struct dirent **namelist, int *n_files);
int resize_panels(WINDOW *left_panel, WINDOW *right_panel);

#endif  // ELTEX_COMMANDER_H
