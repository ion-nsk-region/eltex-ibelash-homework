#ifndef IBELASH_CALC_H
#define IBELASH_CALC_H

#include <dirent.h>
#include <dlfcn.h>
#include <stdio.h>

#define FUNC_MAX 40 // должно быть достаточно на инженерный калькулятор
#define MENU_ERROR -1                    

int menu(char *menu_names[FUNC_MAX], int n_items);
int calc_input(int *a, int *b);
void run_operation(void *func_handle, char *func_name); 
int load_plugins(void *func_handles[FUNC_MAX], char *func_names[FUNC_MAX], char *menu_names[FUNC_MAX], int *n_items);
int get_plugin_symbols(char *plugin_path, void **handle, char **func_name, char **menu_name, unsigned int **menu_pos);
int filter_plugin_names(const struct dirent *entry);
void unload_plugins(void *func_handles[FUNC_MAX]);

#endif // IBELASH_CALC_H
