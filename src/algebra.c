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
    if(a.rows!= b.rows || a.cols!= b.cols)
    {
        printf("Error: Matrix a and b must have the same rows and cols.");
        return create_matrix(0, 0);
    }
    Matrix c = create_matrix(a.rows, a.cols);
    for (int i = 0; i < a.rows; i++)
    {
        for (int j = 0; j < a.cols; j++)
        {
            c.data[i][j] = a.data[i][j] + b.data[i][j];
        }
    }   
    return c;
}

Matrix sub_matrix(Matrix a, Matrix b)
{
    if(a.rows!= b.rows || a.cols!= b.cols)
    {
        printf("Error: Matrix a and b must have the same rows and cols.");
        return create_matrix(0, 0);
    }
    Matrix c = create_matrix(a.rows, a.cols);
    for (int i = 0; i < a.rows; i++)
    {
        for (int j = 0; j < a.cols; j++)
        {
            c.data[i][j] = a.data[i][j] - b.data[i][j];
        }
    }
    return c;
}


Matrix mul_matrix(Matrix a, Matrix b)
{
    if(a.cols != b.rows)
    {
        printf("Error: Matrix a's cols must = b'srows.");
        return create_matrix(0, 0);
    }
    Matrix c = create_matrix(a.rows, b.cols);
    for (int i = 0; i < a.rows; i++)
    {
        for (int j = 0; j < b.cols; j++)
        {
            for (int k = 0; k < a.cols; k++)
            {
                c.data[i][j] += a.data[i][k] * b.data[k][j];
            }
        }
    }
    return c;
}

Matrix scale_matrix(Matrix a, double k)
{
    Matrix c = create_matrix(a.rows, a.cols);
    for (int i = 0; i < a.rows; i++)
    {
        for (int j = 0; j < a.cols; j++)
        {
            c.data[i][j] = a.data[i][j] * k;
        }
    }
    return c;
}

Matrix transpose_matrix(Matrix a)
{
    Matrix c = create_matrix(a.cols, a.rows);
    for (int i = 0; i < a.rows; i++)
    {
        for (int j = 0; j < a.cols; j++)
        {
            c.data[j][i] = a.data[i][j];
        }
    }
    return c;
}


double det_matrix(Matrix a)
{
    if(a.rows != a.cols)
    {
        printf("Error: Matrix a must be a square matrix.");
        return 0;
    }

    if(a.rows == 1)
    {
        return a.data[0][0];
    }

    if(a.rows == 2)
    {
        return a.data[0][0] * a.data[1][1] - a.data[0][1] * a.data[1][0];
    }

    double det = 0;
    for (int j = 0; j < a.cols; j++)
    {
        Matrix b = create_matrix(a.rows - 1, a.cols - 1);
        for (int i = 1; i < a.rows; i++)
        {
            int k = 0;
            for (int l = 0; l < a.cols; l++)
            {
                if (l != j)
                {
                    b.data[i - 1][k] = a.data[i][l];
                    k++;
                }
            }
            det += pow(-1, j) * a.data[0][j] * det_matrix(b);
        }
    }
    return det;  
}


Matrix inv_matrix(Matrix a)
{
    if( det_matrix(a) == 0)
    {
        printf("Error: The Matrix must be a square matrix.");
        return create_matrix(0, 0);
    }

    Matrix c = create_matrix(a.rows, a.cols);
    return create_matrix(0, 0); 
}


int rank_matrix(Matrix a)
{
    // ToDo
    return 0;
}

double trace_matrix(Matrix a)
{
    if(a.rows != a.cols)
    {
        printf("Error: Matrix a must be a square matrix.");
        return 0;
    }
    double trace = 0;
    for (int i = 0; i < a.rows; i++)
    {
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