#include <stdio.h>
#include <stdlib.h>

#define MAX_MATRIX_SIZE 100

typedef struct Matrix {
    int rows; // 矩阵的行数
    int cols; // 矩阵的列数
    double data[MAX_MATRIX_SIZE][MAX_MATRIX_SIZE];  // 矩阵的数据
} Matrix;


int rank_matrix(Matrix a);
void swap_rows(double **matrix, int row1, int row2, int cols);
void eliminate_below(double **matrix, int pivot_row, int pivot_col, int rows, int cols);

int main() {

    Matrix A = {3, 3, {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    }};

    int rank = rank_matrix(A);

    printf("Rank of Matrix A: %d\n", rank);

    return 0;
}

int rank_matrix(Matrix a) {
    int rank = 0;
    int rows = a.rows;
    int cols = a.cols;

    // 创建矩阵的副本
    double **matrix = (double **)malloc(rows * sizeof(double *));
    for (int i = 0; i < rows; i++) {
        matrix[i] = (double *)malloc(cols * sizeof(double));
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = a.data[i][j];
        }
    }

    // 使用高斯消元法将矩阵转换为上三角形式
    int min_dimension = (rows < cols) ? rows : cols;
    for (int pivot_row = 0; pivot_row < min_dimension; pivot_row++) {
        // 找到当前列非零元素的行
        int nonzero_row = -1;
        for (int row = pivot_row; row < rows; row++) {
            if (matrix[row][pivot_row] != 0) {
                nonzero_row = row;
                break;
            }
        }
        // 如果找不到非零元素的行，则继续下一列
        if (nonzero_row == -1) {
            continue;
        }
        // 将当前非零元素的行交换到当前行
        if (nonzero_row != pivot_row) {
            swap_rows(matrix, pivot_row, nonzero_row, cols);
        }
        // 将当前列下方的元素消为0
        eliminate_below(matrix, pivot_row, pivot_row, rows, cols);
        rank++;
    }

    // 释放内存空间
    for (int i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);

    return rank;
}

// 函数定义：交换矩阵的两行
void swap_rows(double **matrix, int row1, int row2, int cols) {
    double *temp = matrix[row1];
    matrix[row1] = matrix[row2];
    matrix[row2] = temp;
}

// 函数定义：将当前列下方的元素消为0
void eliminate_below(double **matrix, int pivot_row, int pivot_col, int rows, int cols) {
    double pivot_value = matrix[pivot_row][pivot_col];
    for (int row = pivot_row + 1; row < rows; row++) {
        double factor = matrix[row][pivot_col] / pivot_value;
        for (int col = pivot_col; col < cols; col++) {
            matrix[row][col] -= factor * matrix[pivot_row][col];
        }
    }
}
