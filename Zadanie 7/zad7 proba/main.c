#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

double dot_prod(double *v1, double *v2, size_t size)
{
    double res = 0.0;
    for (int i = 0; i < size; ++i)
    {
        res += v1[i] * v2[i];
    }
    return res;
}

double* vect_scalar_prod(double *v, double n, size_t size)
{
    double *new_v = malloc(size * sizeof(double));
    for (int i = 0; i < size; ++i)
    {
        new_v[i] = n * v[i];
    }
    return new_v;
}

double* vect_add(double *v1, double *v2, size_t size)
{
    double *new_v = malloc(size * sizeof(double));
    for (int i = 0; i < size; ++i)
    {
        new_v[i] = v1[i] + v2[i];
    }
    return new_v;
}

double* vect_sub(double *v1, double *v2, size_t size)
{
    double *new_v = malloc(size * sizeof(double));
    for (int i = 0; i < size; ++i)
    {
        new_v[i] = v1[i] - v2[i];
    }
    return new_v;
}

//i * size -> ith row
//j -> jth col
double* matrix_vect_prod(double *A, double *v, size_t size)
{
    double *new_A = malloc(size * size * sizeof(double));
    for (int i = 0; i < size; ++i)
    {
        new_A[i] = 0.0;
        for (int j = 0; j < size; ++j)
        {
            new_A[i] += A[(i * size) + j] * v[j];
        }
    }
    return new_A;
}

//solves Ax = b
//x - initial guess, can be all zeros
//returns the x vector with actual solution
double* conj_grad_solve(double *A, double *x, double *b, double eps, size_t size)
{
    int iter = 0;

    //helper variables for optimalization
    double r_sq;
    double *Ap;

    //cg variables
    double alpha, beta;
    double *r = malloc(size * sizeof(*r));
    double *p = malloc(size * sizeof(*p));
    double *p_next = malloc(size * sizeof(*p_next));

    //r = b - Ax
    r = vect_sub(b, matrix_vect_prod(A, x, size), size);

    //p = r
    memcpy(p, r, size * sizeof(*r));

    // ||r|| > eps
    while (sqrt((r_sq = dot_prod(r, r, size))) > eps)
    {
        Ap = matrix_vect_prod(A, p, size);

        alpha = r_sq / dot_prod(p, Ap, size);

        //r = r - alpha * Ap
        r = vect_sub(r, vect_scalar_prod(Ap, alpha, size), size);

        //here, r(k) in dot_prod is actually r(k + 1)
        beta = dot_prod(r, r, size) / r_sq;

        //p = r + beta * p
        p_next = vect_add(r, vect_scalar_prod(p, beta, size), size);

        //x = x + alpha * p
        x = vect_add(x, vect_scalar_prod(p, alpha, size), size);

        memcpy(p, p_next, size * sizeof(*p_next));

        /*
        iter++;
        for (int i = 0; i < size; ++i)
        {
            printf("%.16f\n", x[i]);
        }
        */
    }
    //printf("iter: %d\n", iter);
    free(r);
    free(p);
    free(p_next);
    return x;
}

int main()
{
    //compound literals - a c99 feature
    double *A = (double[]){4, -1, 0,/**/ -1, 4, -1,/**/ 0, -1, 4};
    double *x = (double[]){0, 0, 0};
    double *b = (double[]){1, 0, 1};
    const size_t size = 3;

    x = conj_grad_solve(A, x, b, 1e-10, size);

    for (int i = 0; i < size; ++i)
    {
        printf("%.16f\n", x[i]);
    }
}