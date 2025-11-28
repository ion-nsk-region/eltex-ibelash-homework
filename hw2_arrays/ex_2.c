// 2. Вывести заданный массив размером N в обратном порядке *
//    - заполнить массив числами от 1 до N
//    - поменять местами противоположные элементы (первый с последним и т.д.)

#include <stdio.h>

#define N 20  // Максимальный размер массива

void flip_array(int array[N], int array_size);
void generate_array(int array[N], int array_size);
int input(int *number);
void print_array(int array[N], int array_size);

// ==================================================================
int main() {
  int arr[N];
  int array_size;

  printf("Введите размер массива (до %d): ", N);
  if (0 != input(&array_size)) {
    printf("Ошибка: Размер массива может быть только целым числом.\n");
    return 1;
  }
  if (N < array_size) {
    printf("Ошибка: Размер массива должен быть меньше или равен %d.\n", N);
    return 1;
  }

  // заполняем массив
  generate_array(arr, array_size);
  print_array(arr, array_size);

  // разворачиваем массив
  flip_array(arr, array_size);
  print_array(arr, array_size);

  return 0;
}
// ==================================================================

void flip_array(int array[N], int array_size) {
  int tmp, ind_opp;
  int middle = array_size / 2;

  for (int i = 0; i < middle; i++) {
    ind_opp = array_size - i - 1;  // индекс противоположного элемента

    tmp = array[i];
    array[i] = array[ind_opp];
    array[ind_opp] = tmp;
  }
}

void generate_array(int array[N], int array_size) {
  for (int i = 0; i < array_size; i++) {
    array[i] = i + 1;
  }
}

int input(int *number) {
  if (1 != scanf("%d", number)) {
    return 1;
  }
  return 0;
}

void print_array(int array[N], int array_size) {
  printf("%d", array[0]);
  for (int i = 1; i < array_size; i++) {
    printf(" %d", array[i]);
  }
  printf("\n");
}
