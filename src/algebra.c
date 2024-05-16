#include "algebra.h"
#include <stdio.h>
#include <math.h>

Matrix create_matrix(int row, int col)
{
    Matrix m;
    m.rows = row;
    m.cols = col;
    return m;
}

Matrix add_matrix(Matrix a, Matrix b)
{
    Matrix result;

    // 检查矩阵的行数和列数是否相等
    if (a.rows != b.rows || a.cols != b.cols) {
        printf("Error: Matrix a and b must have the same rows and cols.\n");
        result.rows = 0;
        result.cols = 0;
        return result;
    }

    result.rows = a.rows;
    result.cols = a.cols;

    for (int i = 0; i < a.rows; i++) {
        for (int j = 0; j < a.cols; j++) {
            result.data[i][j] = a.data[i][j] + b.data[i][j];
        }
    }

    return result;
}

Matrix sub_matrix(Matrix a, Matrix b)
{
    Matrix result;

    if (a.rows != b.rows || a.cols != b.cols) {
        printf("Error: Matrix a and b must have the same rows and cols.\n");
        result.rows = 0;
        result.cols = 0;
        return result;
    }

    result.rows = a.rows;
    result.cols = a.cols;

    for (int i = 0; i < a.rows; i++) {
        for (int j = 0; j < a.cols; j++) {
            result.data[i][j] = a.data[i][j] - b.data[i][j];
        }
    }

    return result;
}

Matrix mul_matrix(Matrix a, Matrix b)
{
    Matrix result;
    result.rows = a.rows;
    result.cols = b.cols;
    
    if (a.cols != b.rows) {
        printf("Error: The number of cols of matrix a must be equal to the number of rows of matrix b.\n");
        result.rows = 0;
        result.cols = 0;
        return result;
    }

    for (int i = 0; i < a.rows; i++) {
        for (int j = 0; j < b.cols; j++) {
            result.data[i][j] = 0;
            for (int k = 0; k < a.cols; k++) {
                result.data[i][j] += a.data[i][k] * b.data[k][j];
            }
        }
    }

    return result;
}

Matrix scale_matrix(Matrix a, double k)
{
    Matrix result;
    result.rows = a.rows;
    result.cols = a.cols;

    for (int i = 0; i < a.rows; i++) {
        for (int j = 0; j < a.cols; j++) {
            result.data[i][j] = (a.data[i][j] * k);
        }
    }

    return result;
}

Matrix transpose_matrix(Matrix a)
{
    Matrix result;
    result.rows = a.cols;
    result.cols = a.rows;

    for (int i = 0; i < a.rows; i++) {
        for (int j = 0; j < a.cols; j++) {
            result.data[j][i] = a.data[i][j];
        }
    }

    return result;
}

double det_matrix(Matrix a)
{
    if (a.rows != a.cols) {
        printf("Error: The matrix must be a square matrix.\n");
        return 0;
    }
    
    // 递归结束条件：对于1x1的矩阵，直接返回该元素本身
    if (a.rows == 1 && a.cols == 1) {
        return a.data[0][0];
    }

    // 递归结束条件：对于2x2的矩阵
    if (a.rows == 2 && a.cols == 2) {
        return a.data[0][0] * a.data[1][1] - a.data[0][1] * a.data[1][0];
    }

    double det = 0;
    Matrix sub_matrix;

    for (int j = 0; j < a.cols; j++) {
        double cofactor = (j % 2 == 0) ? 1 : -1;
        cofactor *= a.data[0][j];

        // 构建子矩阵
        sub_matrix.rows = a.rows - 1;
        sub_matrix.cols = a.cols - 1;

        for (int i = 1; i < a.rows; i++) {
            int sub_i = i - 1;
            for (int k = 0; k < a.cols; k++) {
                if (k != j) {
                    sub_matrix.data[sub_i][k > j ? k - 1 : k] = a.data[i][k];
                }
            }
        }

        det += cofactor * det_matrix(sub_matrix);
    }

    return det;
}

// 函数定义：创建矩阵的子矩阵
Matrix create_submatrix(Matrix a, int row, int col) {
    Matrix sub_matrix;
    sub_matrix.rows = a.rows - 1;
    sub_matrix.cols = a.cols - 1;

    int sub_i = 0, sub_j = 0;
    for (int i = 0; i < a.rows; i++) {
        if (i == row) continue;
        sub_j = 0;
        for (int j = 0; j < a.cols; j++) {
            if (j == col) continue;
            sub_matrix.data[sub_i][sub_j] = a.data[i][j];
            sub_j++;
        }
        sub_i++;
    }

    return sub_matrix;
}

// 函数定义：计算矩阵的伴随矩阵
Matrix adjugate_matrix(Matrix a) 
{
    Matrix adjugate;
    adjugate.rows = a.rows;
    adjugate.cols = a.cols;

    for (int i = 0; i < a.rows; i++) {
        for (int j = 0; j < a.cols; j++) {
            double sign = ((i + j) % 2 == 0) ? 1 : -1;
            adjugate.data[i][j] = sign * det_matrix(create_submatrix(a, i, j));
        }
    }

    // 转置伴随矩阵以得到最终结果
    adjugate = transpose_matrix(adjugate);

    return adjugate;
}

Matrix inv_matrix(Matrix a)
{
    Matrix result;

    // 检查矩阵是否为方阵
    if (a.rows != a.cols) {
        printf("Error: The matrix must be a square matrix.\n");
        result.rows = 0;
        result.cols = 0;
        return result;
    }

    // 计算矩阵的行列式
    double det = det_matrix(a);

    // 检查矩阵的行列式是否为0
    if (det == 0) {
        printf("Error: The matrix must be a square matrix.\n");
        result.rows = 0;
        result.cols = 0;
        return result;
    }

    // 计算矩阵的伴随矩阵
    Matrix adjugate = adjugate_matrix(a);

    // 计算逆矩阵
    double det_inverse = 1.0 / det;
    result = scale_matrix(adjugate, det_inverse);

    return result;
}

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

int rank_matrix(Matrix a)
{
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

    for (int i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);

    return rank;
}

double trace_matrix(Matrix a)
{

    if (a.rows != a.cols) {
        printf("Error: The matrix must be a square matrix.\n");
        return 0;
    }

    double trace = 0;
    for (int i = 0; i < a.rows; i++) {
        trace += a.data[i][i];
    }

    return trace;
}

void print_matrix(Matrix a)
{
    for (int i = 0; i < a.rows; i++)
    {
        for (int j = 0; j < a.cols; j++)
        {
            // 按行打印，每个元素占8个字符的宽度，小数点后保留2位，左对齐
            printf("%-8.2f", a.data[i][j]);
        }
        printf("\n");
    }
}