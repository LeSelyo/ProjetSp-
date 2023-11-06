#ifndef MATRIX_H
#define MATRIX_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#define MATRIX_INITIAL_CAPACITY 4

typedef struct
{
    int rows;
    int cols;
    double *data;
} Matrix;



Matrix *m_init(Matrix *a, int rows, int cols);

Matrix *m_identity(Matrix *a, int size);

void m_free(Matrix *a);

Matrix *m_setIndex(Matrix *a, int r, int c, double val);

Matrix *m_map_row(Matrix *a, int r, double (*f)(double));

Matrix *m_map_col(Matrix *a, int c, double (*f)(double));

Matrix *m_map(Matrix *a, double (*f)(double));

Matrix *m_add(Matrix *a, Matrix *b);

Matrix *m_subtract(Matrix *a, Matrix *b);

Matrix *m_hadamard(Matrix *a, Matrix *b);

Matrix *m_scalar_mult(Matrix *a, double x);

Matrix *m_scalar_add(Matrix *a, double x);

Matrix *m_mult(Matrix *a, Matrix *b, Matrix *dest);

Matrix *m_transpose(Matrix *a, Matrix *dest);

Matrix *m_copy(Matrix *src, Matrix *dest);

double m_get(Matrix *a, int r, int c);

int m_rows(Matrix *a);

int m_cols(Matrix *a);

double m_sum(Matrix *a);

Matrix *m_colsum(Matrix *a, Matrix *dest);

void m_print(Matrix *a);

void m_full_print(Matrix *a);

bool m_equals(Matrix *a, Matrix *b);

#endif