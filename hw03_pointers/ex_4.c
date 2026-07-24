// 4. Напишите программу, которая ищет во введённой строке (с клавиатуры)
// введенную подстроку (с клавиатуры) и возвращает указатель на начало
// подстроки, если подстрока не найдена в указатель записывается NULL.
// В качестве строк использовать статические массивы.

#include <stdio.h>

int compare_strings(char string1[BUFSIZ], char string2[BUFSIZ], int length);
char *findstr(char string[BUFSIZ], char substring[BUFSIZ]);
int input(char my_string[BUFSIZ]);
void print_string(char string[BUFSIZ], int length, char *hl, int hl_length);
int string_length(char string[BUFSIZ]);

// ==========================================================================
int main() {
  char my_string[BUFSIZ], substring[BUFSIZ], *ptr;
  int res;

  printf("Введите строку: ");
  res = input(my_string);
  if (1 == res) {
    printf("Ошибка: прерванный ввод. Выходим из программы.");
    return 1;
  }
  if (2 == res) {
    printf("Ошибка: пустой ввод. Пожалуйста введите хоть что-нибудь.");
    return 1;
  }

  printf("Введите строку для поиска: ");
  res = input(substring);
  if (1 == res) {
    printf("Ошибка: прерванный ввод. Выходим из программы.");
    return 1;
  }
  if (2 == res) {
    printf("Ошибка: пустой ввод. Пожалуйста введите хоть что-нибудь.");
    return 1;
  }

  // Ищем подстроку в строке
  ptr = findstr(my_string, substring);

  if (NULL == ptr) {
    printf("Подстрока не встречается во введённой строке.\n");
  } else {
    printf("Подстрока найдена по адресу %p\n", ptr);
    print_string(my_string, string_length(my_string), ptr,
                 string_length(substring));
  }

  return 0;
}
// ==========================================================================

int input(char my_string[BUFSIZ]) {
  if (NULL == fgets(my_string, BUFSIZ, stdin)) {
    // ошибка во время ввода/прерванный ввод
    return 1;
  }
  if ('\n' == *my_string) {
    // пустой ввод/ничего не введено
    return 2;
  }
  return 0;
}

char *findstr(char string[BUFSIZ], char substring[BUFSIZ]) {
  char *ptr;
  int length, ss_length;
  length = string_length(string);
  ss_length = string_length(substring);
  if (-1 == length || -1 == ss_length) {
    return NULL;
  }

  for (ptr = string; ptr < string + length - ss_length; ptr++) {
    if (*ptr == *substring) {
      if (0 == compare_strings(ptr, substring, ss_length)) {
        break;
      }
    }
  }

  if (ptr == string + length - ss_length) {
    return NULL;
  }

  return ptr;
}

int compare_strings(char string1[BUFSIZ], char string2[BUFSIZ], int length) {
  // сравниваем две строки одинаковой длины
  for (char *ptr1 = string1, *ptr2 = string2; ptr1 < string1 + length;
       ptr1++, ptr2++) {
    if (*ptr1 != *ptr2) {
      return 1;
    }
  }
  return 0;
}

int string_length(char string[BUFSIZ]) {
  char *ptr = string;
  int length = 0;
  while (*ptr != '\0' && length < BUFSIZ) {
    length++;
    ptr++;
  }
  if (*ptr != '\0') {
    // строка без терминатора
    return -1;
  }
  return --length;
}

void print_string(char string[BUFSIZ], int length, char *hl, int hl_length) {
  char *ptr = string;
  for (int i = 0; i < length; i++, ptr++) {
    if (ptr == hl) {
      printf("\033[4m"); // подчёркиваем
      }
    if (ptr == hl + hl_length) {
      printf("\033[0m");  // сбрасываем форматирование 
    } 
      printf("%c", *ptr);
    
  }
}
