// 4. Заполнить матрицу числами от 1 до N^2 улиткой.

#include <stdio.h>

#define N 20     // максимальный размер матрицы
#define WIDTH 4  // ширина столбца матрицы

int input(unsigned int *number);
void snail_matrix(int matrix[N][N], int matrix_size);
void snail_we(int matrix[N][N], int steps, int start_val, int start_row,
              int start_col);
void snail_ns(int matrix[N][N], int steps, int start_val, int start_row,
              int start_col);
void snail_ew(int matrix[N][N], int steps, int start_val, int start_row,
              int start_col);
void snail_sn(int matrix[N][N], int steps, int start_val, int start_row,
              int start_col);
void print_matrix(int matrix[N][N], int matrix_size);

// =================================================================
int main() {
  int matrix[N][N];
  unsigned int matrix_size;
  // Вводим размер матрицы
  printf("Введите размер квадратной матрицы (до %d): ", N);
  if (0 != input(&matrix_size)) {
    printf("Ошибка: Введено не целое число.\n");
    return 1;
  }
  if (N < matrix_size) {
    printf("Ошибка: Введённый размер матрицы превышает размер буфера.\n");
    printf("        Пожалуйста, введите меньший размер.\n");
    return 1;
  }

  // Генерируем матрицу
  snail_matrix(matrix, matrix_size);

  // Выводим матрицу
  print_matrix(matrix, matrix_size);

  return 0;
}
// =================================================================

int input(unsigned int *number) {
  if (1 != scanf("%u", number)) {
    return 1;
  }
  return 0;
}

void snail_matrix(int matrix[N][N], int matrix_size) {
  int steps = matrix_size, start_val = 1, start_row = 0, start_col = -1;

  while (0 < steps) {
    // идём на восток
    snail_we(matrix, steps, start_val, start_row, ++start_col);
    // идём на юг
    start_val = start_val + steps;
    start_col = start_col + steps - 1;
    snail_ns(matrix, --steps, start_val, ++start_row, start_col);
    // идём на запад
    start_val = start_val + steps;
    start_row = start_row + steps - 1;
    snail_ew(matrix, steps, start_val, start_row, --start_col);
    // идём на север
    start_val = start_val + steps;
    start_col = start_col - steps + 1;
    snail_sn(matrix, --steps, start_val, --start_row, start_col);
    // снова на восток
    start_val = start_val + steps;
    start_row = start_row - steps + 1;
  }
}

void snail_we(int matrix[N][N], int steps, int start_val, int start_row,
              int start_col) {
  for (int i = 0; i < steps; i++) {
    matrix[start_row][start_col + i] = start_val + i;
  }
}

void snail_ns(int matrix[N][N], int steps, int start_val, int start_row,
              int start_col) {
  for (int i = 0; i < steps; i++) {
    matrix[start_row + i][start_col] = start_val + i;
  }
}

void snail_ew(int matrix[N][N], int steps, int start_val, int start_row,
              int start_col) {
  for (int i = 0; i < steps; i++) {
    matrix[start_row][start_col - i] = start_val + i;
  }
}

void snail_sn(int matrix[N][N], int steps, int start_val, int start_row,
              int start_col) {
  for (int i = 0; i < steps; i++) {
    matrix[start_row - i][start_col] = start_val + i;
  }
}

void print_matrix(int matrix[N][N], int matrix_size) {
  for (int i = 0; i < matrix_size; i++) {
    for (int j = 0; j < matrix_size; j++) {
      printf("%-*d", WIDTH, matrix[i][j]);
    }
    printf("\n");
  }
}
