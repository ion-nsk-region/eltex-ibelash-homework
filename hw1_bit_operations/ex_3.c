// 3. Найти количество единиц в двоичном представлении целого
// положительного числа (число вводится с клавиатуры).

#include <limits.h>
#include <stdio.h>

int input(unsigned int *number);
int population_count_k_r(unsigned int number);
int population_count_simple(unsigned int number);

// ==========================================================
int main() {
  unsigned int number, result;

  printf("Введите целое положительное число до %u: ", UINT_MAX);
  if (0 != input(&number)) {
    printf("Ошибка: введено не целое число.\n");
    return 1;
  }

  result = population_count_k_r(number);
  //    result = population_count_simple(number);

  printf("Количество единиц в двоичном представлении числа %u: %u\n", number,
         result);
#if __GLIBC__ > 2 || (__GLIBC__ == 2 && __GLIBC_MINOR__ > 35)
  printf("Для ручной проверки: %0*b\n", (int)(8 * sizeof(number)), number);
#endif
  return 0;
}
// ==========================================================

int input(unsigned int *number) {
  if (1 != scanf("%u", number)) {
    return 1;
  }
  return 0;
}

int population_count_simple(unsigned int number) {
  int counter = 0;
  int n = 8 * sizeof(number);
  for (int i = 0; i < n; i++) {
    if (0x1 & (number >> i)) {
      counter++;
    }
  }
  return counter;
}

int population_count_k_r(unsigned int number) {
  // Алгоритм подсчёта единиц из K&R или "Communications of the ACM" март 1960го
  // статья за авторством Peter Wegner
  // https://graphics.stanford.edu/~seander/bithacks.html#CountBitsSetKernighan
  int counter = 0;
  while (0 < number) {
    number = number & (number - 1);
    counter++;
  }
  return counter;
}
