#include <iostream>
#include <cassert>
#include "../src/matrix.h"
#include "../src/strassen.h"

void test_matrix_multiplication() {
    const int size = 4; // Example size for testing
    int** A = allocate_matrix(size, size);
    int** B = allocate_matrix(size, size);
    int** C_regular = allocate_matrix(size, size);
    int** C_strassen = allocate_matrix(size, size);

    // Fill matrices with known values
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            A[i][j] = i + j; // Simple pattern
            B[i][j] = i - j; // Simple pattern
        }
    }

    // Perform regular multiplication
    multiply_regular(size, A, B, C_regular);

    // Perform Strassen multiplication
    multiply_strassen(size, A, B, C_strassen);

    // Compare results
    int errors = compare_matrices(C_regular, C_strassen, size);
    assert(errors == 0 && "Strassen multiplication did not match regular multiplication!");

    // Clean up
    free_matrix(A);
    free_matrix(B);
    free_matrix(C_regular);
    free_matrix(C_strassen);
}

int main() {
    test_matrix_multiplication();
    std::cout << "All tests passed!" << std::endl;
    return 0;
}