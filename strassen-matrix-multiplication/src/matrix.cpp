#include "matrix.h"
#include <cstdlib>
#include <ctime>

int** allocate_matrix(int rows, int cols) {
    int* data_block = new int[rows * cols];
    int** matrix = new int*[rows];
    for (int i = 0; i < rows; ++i) {
        matrix[i] = data_block + i * cols;
    }
    return matrix;
}

void free_matrix(int** matrix) {
    delete[] matrix[0];  
    delete[] matrix;     
}

void fill_random_matrix(int** matrix, int size) {
    for (int i = 0; i < size; ++i)
        for (int j = 0; j < size; ++j)
            matrix[i][j] = rand() % 10;
}

void add_matrix(int** T, int** A, int** B, int m, int n) {
    for (int i = 0; i < m; ++i)
        for (int j = 0; j < n; ++j)
            T[i][j] = A[i][j] + B[i][j];
}

void subtract_matrix(int** T, int** A, int** B, int m, int n) {
    for (int i = 0; i < m; ++i)
        for (int j = 0; j < n; ++j)
            T[i][j] = A[i][j] - B[i][j];
}