// 4. Напишите программу, которая ищет во введённой строке (с клавиатуры)
// введенную подстроку (с клавиатуры) и возвращает указатель на начало
// подстроки, если подстрока не найдена в указатель записывается NULL.
// В качестве строк использовать статические массивы.

#include <stdio.h>
#include <string.h>

int main() {
  char my_string[BUFSIZ], substring[BUFSIZ], *ptr;
  int res;

  res = input(my_string);
  if (1 == res) {
    printf("Ошибка: прерванный ввод. Выходим из программы.");
    return 1;
  }
  if (2 == res) {
    printf("Ошибка: пустой ввод. Пожалуйста введите хоть что-нибудь.");
    return 1;
  }

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
  ptr = strstr(my_string, substring);

  if (NULL == ptr) {
    printf("Подстрока не встречается во введённой строке.\n");
    return 0;
  }

  return 0;
}

int input(char my_string[BUFSIZ]) {
  if (NULL == fgets(my_string, sizeof(my_string), stdin)) {
    // ошибка во время ввода/прерванный ввод
    return 1;
  }
  if ('\n' == my_string) {
    // пустой ввод/ничего не введено
    return 2;
  }

  return 0;
}
