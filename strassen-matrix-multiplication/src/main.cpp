#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <omp.h>
#include "matrix.h"
#include "strassen.h"

using std::cout;
using std::endl;

int main(int argc, char *argv[])
{
    if (argc < 4)
    {
        cout << "Usage: ./program k k1 threads" << endl;
        return 1;
    }

    int k = std::atoi(argv[1]);
    int k1 = std::atoi(argv[2]);
    int threads_power = std::atoi(argv[3]);

    terminal_matrix_size = (k < k1) ? 1 : std::pow(2, k - k1);
    int num_threads = std::pow(2, threads_power);
    int size = std::pow(2, k);

    omp_set_num_threads(num_threads);
    srand((unsigned)time(NULL));

    int **A = allocate_matrix(size, size);
    int **B = allocate_matrix(size, size);
    int **C = allocate_matrix(size, size);
    int **test = allocate_matrix(size, size);

    fill_random_matrix(A, size);
    fill_random_matrix(B, size);

    double start = omp_get_wtime();
    multiply_strassen(size, A, B, C);
    double end = omp_get_wtime();

    multiply_regular(size, A, B, test);
    int errors = compare_matrices(C, test, size);

    cout << (errors == 0 ? "Success" : "Fail")
         << ": Size=" << size
         << ", K'=" << k1
         << ", Threads=" << num_threads
         << ", Time=" << (end - start)
         << "s, Errors=" << errors << endl;

    free_matrix(A);
    free_matrix(B);
    free_matrix(C);
    free_matrix(test);

    return 0;
}