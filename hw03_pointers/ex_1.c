// 1. Поменять в целом положительном числе (типа int) значение третьего
// байта на введенное пользователем число (изначальное число также
// вводится с клавиатуры) через указатель (не применяя битовые операции).

#include <limits.h>
#include <stdio.h>

void change_3d_byte(int *number, char byte);
int input(int *number);
void print_in_binary(int number);

// ====================================================================
int main() {
  int number, buf;
  unsigned char my_byte;

  printf("Введите целое число от %d до %d: ", INT_MIN, INT_MAX);
  if (0 != input(&number)) {
    printf("Ошибка: Введено не целое число.\n");
    return 1;
  }
  printf("Введите число для третьего байта от 0 до 255: ");
  if (0 != input(&buf)) {
    printf("Ошибка: Введено не целое число.\n");
    return 1;
  }
  if (0 > buf || 255 < buf) {
    printf("Ошибка: Введённое число не умещается в байт.\n");
    printf("        Пожалуйста, вводите число от 0 до 255.\n");
    return 2;
  }
#if __GLIBC__ > 2 || (__GLIBC__ == 2 && __GLIBC_MINOR__ > 35)
  printf("Исходное число:   %0*b\n", (int)(8 * sizeof(number)), number);
#else
  printf("Исходное число:   ");
  print_in_binary(number);
  printf("\n");
#endif

  my_byte = (char)buf;
  change_3d_byte(&number, my_byte);

#if __GLIBC__ > 2 || (__GLIBC__ == 2 && __GLIBC_MINOR__ > 35)
  printf("Изменённое число: %0*b\n", (int)(8 * sizeof(number)), number);
  printf("Байт: %0*b\n", (int)(8 * sizeof(my_byte)), my_byte);
#else
  printf("\nИзменённое число: ");
  print_in_binary(number);
  printf("\n");
  printf("\nБайт: ");
  print_in_binary(my_byte);
  printf("\n");
#endif

  return 0;
}
// ====================================================================

int input(int *number) {
  if (1 != scanf("%d", number)) {
    return 1;
  }
  return 0;
}

void change_3d_byte(int *number, char byte) {
  char *byte_pointer;
  byte_pointer = (char *)number;
  byte_pointer += 2;
  *byte_pointer = byte;
}

void print_in_binary(int number) {
  for (int i = (8 * sizeof(number)) - 1; i >= 0; i--) {
    printf("%d", (number >> i) & 0x1);
  }
}
