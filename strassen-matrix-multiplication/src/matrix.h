#ifndef MATRIX_H
#define MATRIX_H

// Function to allocate a matrix of given rows and columns
int** allocate_matrix(int rows, int cols);

// Function to free the allocated matrix
void free_matrix(int** matrix);

// Function to fill a matrix with random integers
void fill_random_matrix(int** matrix, int size);

// Function to add two matrices: T = A + B
void add_matrix(int** T, int** A, int** B, int m, int n);

// Function to subtract two matrices: T = A - B
void subtract_matrix(int** T, int** A, int** B, int m, int n);

#endif // MATRIX_H