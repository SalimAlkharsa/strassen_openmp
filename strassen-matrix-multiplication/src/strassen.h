#ifndef STRASSEN_H
#define STRASSEN_H

// Global variable for threshold to switch to regular multiplication
extern int terminal_matrix_size;

// Naive matrix multiplication
void multiply_regular(int size, int **A, int **B, int **C);

// Function to perform Strassen's matrix multiplication
void multiply_strassen(int size, int **A, int **B, int **C);

// Helper function to reference a submatrix
void reference_submatrix(int **dst, int **src, int row_offset, int col_offset, int size);

// Function to compare two matrices for equality
int compare_matrices(int **A, int **B, int size);

#endif // STRASSEN_H