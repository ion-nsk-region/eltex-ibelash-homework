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
int list_dir(const char dir_path[PATH_MAX], struct dirent ***namelist,
             int *n_files);
int print_dir(WINDOW *panel, struct dirent **namelist, int n_files, int select);
int resize_panels(WINDOW *left_panel, WINDOW *left_content, WINDOW *right_panel,
                  WINDOW *right_content);
void print_all(WINDOW *left_panel, WINDOW *left_content,
               struct dirent **left_list, int left_nfiles, WINDOW *right_panel,
               WINDOW *right_content, struct dirent **right_list,
               int right_nfiles, WINDOW *active_content, int active_select);
int init_colors(void);
void refresh_all(WINDOW *left_panel, WINDOW *left_content, WINDOW *right_panel,
                 WINDOW *right_content);
void switch_data(const char *src_path, struct dirent **src_list, int src_nfiles, int src_select, const char **dst_path, struct dirent ***dst_list, int *dst_nfiles, int *dst_select);


// void debug(WINDOW *left_panel, WINDOW *left_content, WINDOW *right_panel, WINDOW *right_content, int active_select);
// void debug(const char *path, char *path_buffer);
void debug(char *path_buffer, char *namelist);

#endif  // ELTEX_COMMANDER_H
