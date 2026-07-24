#ifndef IBELASH_CALC_H
#define IBELASH_CALC_H

#include <stdio.h>

enum menu_items {
    MENU_ERROR = -1,
    MENU_ADD = 1,
    MENU_SUB,
    MENU_MUL,
    MENU_DIV,
    MENU_EXIT
};

int menu();
int calc_input(int *a, int *b);
void calc_add(void);
void calc_sub(void);
void calc_mul(void);
void calc_div(void);


#endif // IBELASH_CALC_H
