#include "global.h"
#include <cmath>
#include <gsl/gsl_permutation.h>
#include <gsl/gsl_linalg.h>

Coord sate_coord[4];

float64 getNorm(const Coord & src)
{
    return sqrt(src.x*src.x + src.y*src.y + src.z*src.z);
}

void gsl_matrix_mul(gsl_matrix *a, gsl_matrix *b, gsl_matrix *c) //矩阵乘运算 c=ab
{
    for (size_t i = 0; i<a->size1; i++)
    {
        for (size_t j = 0; j<b->size2; j++)
        {
            float64 sum = 0.0;
            for (size_t k = 0; k<b->size1; k++)
            {
                sum += gsl_matrix_get(a, i, k)*gsl_matrix_get(b, k, j);
            }
            gsl_matrix_set(c, i, j, sum);
        }
    }
}

void GetInverse(gsl_matrix *A, gsl_matrix *inverse)  //矩阵求逆
{
    int n = A->size1;
    gsl_matrix *tmpA = gsl_matrix_alloc(n, n);
    gsl_matrix_memcpy(tmpA, A);
    gsl_permutation *p = gsl_permutation_alloc(n);
    int sign = 0;
    gsl_linalg_LU_decomp(tmpA, p, &sign);
    inverse = gsl_matrix_alloc(n, n);
    gsl_linalg_LU_invert(tmpA, p, inverse);
    gsl_permutation_free(p);
    gsl_matrix_free(tmpA);
}
