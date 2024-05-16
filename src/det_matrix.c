#include <stdio.h>

#define MAX_MATRIX_SIZE 100

typedef struct Matrix
{
    int rows;
    int cols;
    double data[MAX_MATRIX_SIZE][MAX_MATRIX_SIZE];
} Matrix;


double det_matrix(Matrix a);
Matrix create_submatrix(Matrix a, int row, int col);
Matrix adjugate_matrix(Matrix a);
Matrix scale_matrix(Matrix a, double k);
Matrix adjugate_matrix(Matrix a);
Matrix transpose_matrix(Matrix a);

int main()
{
        Matrix A = {3, 3, {
        {2, -1, 0},
        {-1, 2, -1},
        {0, -1, 2}
    }};

    printf("%lf",det_matrix(A));

    return 0;
}


double det_matrix(Matrix a)
{
    // 递归结束条件：对于1x1的矩阵，直接返回该元素本身
    if (a.rows == 1 && a.cols == 1)
    {
        return a.data[0][0];
    }

    // 递归结束条件：对于2x2的矩阵
    if (a.rows == 2 && a.cols == 2)
    {
        return a.data[0][0] * a.data[1][1] - a.data[0][1] * a.data[1][0];
    }

    double det = 0;
    Matrix sub_matrix;

    for (int j = 0; j < a.cols; j++)
    {
        double cofactor = (j % 2 == 0) ? 1 : -1;
        cofactor *= a.data[0][j];

        sub_matrix = create_submatrix(a, 0, j);
  
        det += cofactor * det_matrix(sub_matrix);
    }

    return det;
}

// 函数定义：创建矩阵的子矩阵
Matrix create_submatrix(Matrix a, int row, int col)
{
    Matrix sub_matrix;
    sub_matrix.rows = a.rows - 1;
    sub_matrix.cols = a.cols - 1;

    int sub_i = 0, sub_j = 0;
    for (int i = 0; i < a.rows; i++)
    {
        if (i == row)
            continue;
        sub_j = 0;
        for (int j = 0; j < a.cols; j++)
        {
            if (j == col)
                continue;
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

    for (int i = 0; i < a.rows; i++)
    {
        for (int j = 0; j < a.cols; j++)
        {
            double sign = ((i + j) % 2 == 0) ? 1 : -1;
            adjugate.data[i][j] = sign * det_matrix(create_submatrix(a, i, j));
        }
    }

    // 转置伴随矩阵以得到最终结果
    adjugate = transpose_matrix(adjugate);

    return adjugate;
}

// 函数定义：矩阵转置
Matrix transpose_matrix(Matrix a)
{
    Matrix result;
    result.rows = a.cols;
    result.cols = a.rows;

    for (int i = 0; i < a.rows; i++)
    {
        for (int j = 0; j < a.cols; j++)
        {
            result.data[j][i] = a.data[i][j];
        }
    }

    return result;
}

// 函数定义：矩阵数乘
Matrix scale_matrix(Matrix a, double k)
{
    Matrix result;
    result.rows = a.rows;
    result.cols = a.cols;

    for (int i = 0; i < a.rows; i++)
    {
        for (int j = 0; j < a.cols; j++)
        {
            result.data[i][j] = a.data[i][j] * k;
        }
    }

    return result;
}
