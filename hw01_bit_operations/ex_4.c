// 4. Поменять в целом положительном числе (типа int) значение третьего
// байта на введенное пользователем число (изначальное число также
// вводится с клавиатуры).

#include <limits.h>
#include <stdio.h>

int input(unsigned int *number);
int input_byte(unsigned char *byte);
unsigned int change_3d_byte(unsigned int number, unsigned char byte);
void print_in_binary(unsigned int number);

int main() {
  unsigned int number, res;
  unsigned char my_byte;

  printf("Введите целое положительное число до %u: ", UINT_MAX);
  if (0 != input(&number)) {
    printf("Ошибка: введено не целое число.\n");
    return 1;
  }

  printf("Введите целое число для 3го байта в диапазоне 0..255: ");
  res = input_byte(&my_byte);
  if (1 == res) {
    printf("Ошибка: введено не целое число.\n");
    return 1;
  }
  if (2 == res) {
    printf("Ошибка: число за пределами диапазона 0..255.\n");
    return 1;
  }

  res = change_3d_byte(number, my_byte);

#if __GLIBC__ > 2 || (__GLIBC__ == 2 && __GLIBC_MINOR__ > 35)
  printf("Исходное число: %0*b\n", (int)(8 * sizeof(number)), number);
  printf("Введённый байт: %0*b\n", (int)(8 * sizeof(my_byte)), my_byte);
  printf("Изменённое:     %0*b\n", (int)(8 * sizeof(res)), res);
#else
  printf("Исходное число: ");
  print_in_binary(number);
  printf("\nВведённый байт: ");
  print_in_binary(my_byte);
  printf("\nИзменённое:     ");
  print_in_binary(res);
#endif

  return 0;
}

int input(unsigned int *number) {
  if (1 != scanf("%u", number)) {
    return 1;
  }
  return 0;
}

int input_byte(unsigned char *byte) {
  unsigned int buf;
  if (1 != scanf("%u", &buf)) {
    return 1;
  }
  if (255 < buf) {
    return 2;
  }

  *byte = buf;
  return 0;
}

unsigned int change_3d_byte(unsigned int number, unsigned char byte) {
  unsigned int buf = byte;
  // смещаем присвоенный байт
  buf = buf << (2 * 8);

  // обнуляем третий байт
  number = (number & 0xff00ffff);

  // записываем новое значение
  number = (number | buf);

  return number;
}

void print_in_binary(unsigned int number) {
  for (int i = (int)(8 * sizeof(number)) - 1; i >= 0; i--) {
    printf("%d", (number >> i) & 0x1);
  }
}
