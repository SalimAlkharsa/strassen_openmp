# Strassen Matrix Multiplication

This project implements the Strassen matrix multiplication algorithm, which is an efficient method for multiplying two matrices. The algorithm reduces the complexity of matrix multiplication from O(n^3) to approximately O(n^2.81) by dividing the matrices into smaller submatrices and recursively calculating their products.

## Overview

The project consists of the following components:

- **Matrix Operations**: Functions for allocating, deallocating, and manipulating matrices.
- **Strassen Algorithm**: Implementation of the Strassen matrix multiplication algorithm.
- **Testing**: Unit tests to verify the correctness of both the Strassen and regular matrix multiplication implementations.

## Files

- `src/main.cpp`: The main entry point of the program that handles command-line arguments, initializes matrices, and calls the multiplication functions.
- `src/matrix.h` / `src/matrix.cpp`: Header and implementation files for matrix operations.
- `src/strassen.h` / `src/strassen.cpp`: Header and implementation files for the Strassen algorithm.
- `tests/test_multiplication.cpp`: Unit tests for validating the matrix multiplication functions.
- `CMakeLists.txt`: CMake configuration file for building the project.
- `Makefile`: Makefile for building the project using the make tool.
- `.gitignore`: Specifies files and directories to be ignored by Git.

## Building the Project

To build the project, you can use either CMake or Make.

### Using Make

Simply run:

```
make
```

## Running the Program

After building the project, you can run the program with the following command:

```
./program k k1 threads
```

Where:

- `k` is the exponent for the size of the matrices (size = 2^k).
- `k1` is used to determine the threshold for switching to regular multiplication.
- `threads` specifies the number of threads to use for parallel execution.

## Dependencies

This project requires OpenMP for parallel processing. Ensure that your compiler supports OpenMP.

## License

This project is licensed under the MIT License. See the LICENSE file for more details.
