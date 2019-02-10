// Linear Algebra functions
// Created by Seth Taddiken 2/9/2018

#include <stdio.h>
#include <stdlib.h>

// matrix struct
struct matrix
{
    double** mat;
    int rows;
    int cols;
};
typedef struct matrix matrix; // so that "matrix" can be used in place of "struct matrix"

// prototypes
double** create_mat(int _rows, int _cols);
void print_mat(matrix* _mat);
matrix* mult_mats(matrix* _mat1, matrix* _mat2);
matrix* new_mat(int _rows, int _cols);

int main()
{
    // get matrix dimensions
    int m1;
    int n1;
    int m2;
    int n2;
    printf("Multiply some matrices!\n");
    printf("matrix 1 dimensions (m by n):\n");
    scanf("%d", &m1);
    printf("by\n");
    scanf("%d", &n1);
    printf("matrix 2 dimensions (m by n):\n");
    scanf("%d", &m2);
    printf("by\n");
    scanf("%d", &n2);
    // fill matrices with values
    printf("matrix 1 elements:\n");
    matrix* mat1 = new_mat(m1,n1);
    printf("matrix 2 elements:\n");
    matrix* mat2 = new_mat(m2,n2);
    // multiply matrices
    matrix* mult = mult_mats(mat1, mat2);

    // print out results
    printf("\nmatrix1:\n");
    print_mat(mat1);
    printf("\nmatrix2:\n");
    print_mat(mat2);
    printf("\nmatrix1 * matrix2:\n");
    print_mat(mult);
    printf("\n");

    return 0;
}

// construct a matrix struct
matrix* new_mat(int _rows, int _cols)
{
    matrix* mat = (matrix*)malloc(sizeof(matrix));
    mat->mat = create_mat(_rows, _cols);
    mat->rows = _rows;
    mat->cols = _cols;
    return mat;
}

// initialize matrix memory
double** init_mat(int _rows, int _cols)
{
    double** mat;
    mat = (double**)malloc(_rows * sizeof(double*));
    for (int i = 0; i < _rows; i++)
    {
        mat[i] = (double*)malloc(_cols * sizeof(double));
    }
    return mat;
}

// fill matrix
double** create_mat(int _rows, int _cols)
{
    double** mat = init_mat(_rows, _cols);
    for (int i = 0; i < _rows; i++)
    {
        for (int j = 0; j < _cols; j++)
        {
            double val;
            printf("Value at (%d,%d): ", i, j);
            scanf("%lf", &val);
            mat[i][j] = val;
        }
    }
    return mat;
}

// print matrix
void print_mat(matrix* _mat)
{
    int cols = _mat->cols;
    int rows = _mat->rows;
    double** mat = _mat->mat;

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            printf("%0.2lf ", mat[i][j]);
        }
        printf("\n");
    }
}

// multiply matrices
matrix* mult_mats(matrix* _mat1, matrix* _mat2)
{
    int rows1 = _mat1->rows;
    int cols1 = _mat1->cols;
    int rows2 = _mat2->rows;
    int cols2 = _mat2->cols;
    double** mat1 = _mat1->mat;
    double** mat2 = _mat2->mat;

    if (cols1 != rows2)
    {
        printf("ERROR: Matrices not compatible for multiplication\n");
        return NULL;
    }

    double** mat = init_mat(rows1, cols2);

    for (int i = 0; i < rows1; i++)
    {
        for (int j = 0; j < cols2; j++)
        {
            int dotSum = 0; // the dot product of _mat1's row and _mat2's column
            for (int k = 0; k < cols1; k++) // cols1 == rows2
            {
                dotSum += mat1[i][k] * mat2[k][j];
            }
            mat[i][j] = dotSum;
        }
    }

    matrix* new_mat = (matrix*)malloc(sizeof(matrix));
    new_mat->mat = mat;
    new_mat->rows = rows1;
    new_mat->cols = cols2;

    return new_mat;
}