#include "strassen.h"
#include "matrix.h"
#include <omp.h>
#include <cmath>

// Global variable definition
int terminal_matrix_size;

// Naive matrix multiplication
void multiply_regular(int size, int **A, int **B, int **C)
{
    for (int i = 0; i < size; ++i)
        for (int j = 0; j < size; ++j)
        {
            int sum = 0;
            for (int k = 0; k < size; ++k)
                sum += A[i][k] * B[k][j];
            C[i][j] = sum;
        }
}

// Helper function to reference a submatrix
void reference_submatrix(int **dst, int **src, int row_offset, int col_offset, int size)
{
    for (int i = 0; i < size; ++i)
        dst[i] = src[row_offset + i] + col_offset;
}

// Strassen's Matrix Multiplication
void multiply_strassen(int size, int **A, int **B, int **C)
{
    if (size <= terminal_matrix_size)
    {
        multiply_regular(size, A, B, C);
        return;
    }

    int half = size / 2;

    // Create submatrix references
    int **A11 = new int *[half];
    int **A12 = new int *[half];
    int **A21 = new int *[half];
    int **A22 = new int *[half];
    int **B11 = new int *[half];
    int **B12 = new int *[half];
    int **B21 = new int *[half];
    int **B22 = new int *[half];
    int **C11 = new int *[half];
    int **C12 = new int *[half];
    int **C21 = new int *[half];
    int **C22 = new int *[half];

    reference_submatrix(A11, A, 0, 0, half);
    reference_submatrix(A12, A, 0, half, half);
    reference_submatrix(A21, A, half, 0, half);
    reference_submatrix(A22, A, half, half, half);
    reference_submatrix(B11, B, 0, 0, half);
    reference_submatrix(B12, B, 0, half, half);
    reference_submatrix(B21, B, half, 0, half);
    reference_submatrix(B22, B, half, half, half);
    reference_submatrix(C11, C, 0, 0, half);
    reference_submatrix(C12, C, 0, half, half);
    reference_submatrix(C21, C, half, 0, half);
    reference_submatrix(C22, C, half, half, half);

    // Allocate result matrices
    int **M1 = allocate_matrix(half, half);
    int **M2 = allocate_matrix(half, half);
    int **M3 = allocate_matrix(half, half);
    int **M4 = allocate_matrix(half, half);
    int **M5 = allocate_matrix(half, half);
    int **M6 = allocate_matrix(half, half);
    int **M7 = allocate_matrix(half, half);

    // Allocate unique temp matrices for each task
    int **T1_1 = allocate_matrix(half, half), **T2_1 = allocate_matrix(half, half);
    int **T1_2 = allocate_matrix(half, half), **T2_2 = nullptr;
    int **T1_3 = nullptr, **T2_3 = allocate_matrix(half, half);
    int **T1_4 = nullptr, **T2_4 = allocate_matrix(half, half);
    int **T1_5 = allocate_matrix(half, half), **T2_5 = nullptr;
    int **T1_6 = allocate_matrix(half, half), **T2_6 = allocate_matrix(half, half);
    int **T1_7 = allocate_matrix(half, half), **T2_7 = allocate_matrix(half, half);

#pragma omp parallel
#pragma omp single
    {
#pragma omp task
        {
            add_matrix(T1_1, A11, A22, half, half);
            add_matrix(T2_1, B11, B22, half, half);
            multiply_strassen(half, T1_1, T2_1, M1);
        }

#pragma omp task
        {
            add_matrix(T1_2, A21, A22, half, half);
            multiply_strassen(half, T1_2, B11, M2);
        }

#pragma omp task
        {
            subtract_matrix(T2_3, B12, B22, half, half);
            multiply_strassen(half, A11, T2_3, M3);
        }

#pragma omp task
        {
            subtract_matrix(T2_4, B21, B11, half, half);
            multiply_strassen(half, A22, T2_4, M4);
        }

#pragma omp task
        {
            add_matrix(T1_5, A11, A12, half, half);
            multiply_strassen(half, T1_5, B22, M5);
        }

#pragma omp task
        {
            subtract_matrix(T1_6, A21, A11, half, half);
            add_matrix(T2_6, B11, B12, half, half);
            multiply_strassen(half, T1_6, T2_6, M6);
        }

#pragma omp task
        {
            subtract_matrix(T1_7, A12, A22, half, half);
            add_matrix(T2_7, B21, B22, half, half);
            multiply_strassen(half, T1_7, T2_7, M7);
        }
    }

#pragma omp taskwait

    // Combine results into C
    for (int i = 0; i < half; ++i)
        for (int j = 0; j < half; ++j)
        {
            C11[i][j] = M1[i][j] + M4[i][j] - M5[i][j] + M7[i][j];
            C12[i][j] = M3[i][j] + M5[i][j];
            C21[i][j] = M2[i][j] + M4[i][j];
            C22[i][j] = M1[i][j] - M2[i][j] + M3[i][j] + M6[i][j];
        }

    // Free memory
    free_matrix(M1);
    free_matrix(M2);
    free_matrix(M3);
    free_matrix(M4);
    free_matrix(M5);
    free_matrix(M6);
    free_matrix(M7);

    free_matrix(T1_1);
    free_matrix(T2_1);
    free_matrix(T1_2);
    free_matrix(T2_3);
    free_matrix(T2_4);
    free_matrix(T1_5);
    free_matrix(T1_6);
    free_matrix(T2_6);
    free_matrix(T1_7);
    free_matrix(T2_7);

    delete[] A11;
    delete[] A12;
    delete[] A21;
    delete[] A22;
    delete[] B11;
    delete[] B12;
    delete[] B21;
    delete[] B22;
    delete[] C11;
    delete[] C12;
    delete[] C21;
    delete[] C22;
}

// Compare two matrices for equality
int compare_matrices(int **A, int **B, int size)
{
    int errors = 0;
    for (int i = 0; i < size; ++i)
        for (int j = 0; j < size; ++j)
            if (A[i][j] != B[i][j])
                ++errors;
    return errors;
}