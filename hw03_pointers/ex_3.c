// 3. Напишите программу, в которой определите массив типа int (размер
// массива 10 элементов от 1 до 10). Используйте указатель для вывода
// элементов массива на консоль (применять можно только арифметику
// указателей, а не индексы).

#include <stdio.h>

#define N 10

void populate_array(int arr[N], int array_size);
void print_array(int arr[N], int array_size);

// ========================================================================
int main() {
  int arr[N], array_size = N;

  populate_array(arr, array_size);
  print_array(arr, array_size);

  return 0;
}
// ========================================================================

void populate_array(int arr[N], int array_size) {
  for (int i = 1, *p = arr; p < (arr + array_size); p++, i++) {
    *p = i;
  }
}

void print_array(int arr[N], int array_size) {
  printf("%d", *arr);
  for (int *p = (arr + 1); p < (arr + array_size); p++) {
    printf(" %d", *p);
  }
  printf("\n");
}
