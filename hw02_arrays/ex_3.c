// 3. Заполнить верхний треугольник нулями, а диагональ и нижний треугольник
// единицами. Каждый элемент заполняется в цикле по формуле, а не вручную.
// Размер массива статический.

#include <stdio.h>

#define N 20     // максимальный размер матрицы
#define WIDTH 2  // ширина столбца матрицы

int input(unsigned int *number);
void triangle_matrix(int matrix[N][N], int matrix_size);
void print_matrix(const int matrix[N][N], int matrix_size);

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

  // Заполняем матрицу
  triangle_matrix(matrix, matrix_size);

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

void triangle_matrix(int matrix[N][N], int matrix_size) {
  for (int i = 0; i < matrix_size; i++) {
    for (int j = 0; j < matrix_size; j++) {
      if (i + j >= matrix_size - 1) {
        matrix[i][j] = 1;
      } else {
        matrix[i][j] = 0;
      }
    }
  }
}

void print_matrix(const int matrix[N][N], int matrix_size) {
  for (int i = 0; i < matrix_size; i++) {
    for (int j = 0; j < matrix_size; j++) {
      printf("%-*d", WIDTH, matrix[i][j]);
    }
    printf("\n");
  }
}
