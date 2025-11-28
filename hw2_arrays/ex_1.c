// 1. Вывести квадратную матрицу по заданному N

#include <stdio.h>

#define N 20    // максимальный размер матрицы
#define WIDTH 4 // ширина столбца матрицы

int input(unsigned int *number); 
void generate_matrix(int matrix[N][N], int matrix_size); 
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
    generate_matrix(matrix, matrix_size);
    
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

void generate_matrix(int matrix[N][N], int matrix_size) {
    for (int i = 0; i < matrix_size * matrix_size; i++) {
        matrix[i / matrix_size][i % matrix_size] = i + 1;
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

