//
// Created by Hadrien BAILLY on 11/03/2022.
//

#ifndef DCU_MATRIX_H
#define DCU_MATRIX_H

#include <stdlib.h>
#include <stdio.h>
#include "unistd.h"

#include <omp.h>

#include "../utils/log_util.h"
#include "../exceptions/exception.h"

#define MATRIX_FILE_EXT "mtx"

/**
 * The structure representing a matrix in memory.
 */
typedef struct Matrix {
    int **values;
    char *name;
    unsigned int height;
    unsigned int width;
} Matrix;

/**
 * Return a new matrix.
 * @param name the name of the matrix to instantiate.
 * @return a new matrix instance.
 */
Matrix *create_empty_matrix(char *name);

/**
 * Allocate heap memory to a given matrix
 * @param matrix the matrix for which allocate memory.
 * @throw INVALID_MATRIX_DIMENSION if the matrix has any dimension equal to 0.
 */
void allocate_memory(Matrix *matrix);

/**
 * Returns a new matrix with allocated memory.
 * @param name the name of the matrix to create.
 * @param height the height of the matrix to create.
 * @param width the width of the matrix to create.
 * @return a new instance of a matrix with a [height,width] heap memory allocation.
 * @throw INVALID_MATRIX_DIMENSION if the matrix has any dimension equal to 0.
 */
Matrix *create_matrix(char *name, unsigned int height, unsigned int width);

/**
 * Free and remove the given matrix from the heap.
 * @param matrix the matrix to destroy.
 */
void destroy_matrix(Matrix *matrix);

/**
 * Display the given matrix on screen.
 * @param matrix the matrix to display.
 */
void display_matrix(Matrix *matrix);

/**
 * Check if two matrices are equal re. their data.
 * @param A the first matrix to compare.
 * @param B the second matrix to compare.
 * @return true if both matrices contain the same values.
 * @throw INVALID_MATRIX_DIMENSION if the matrices' dimensions do not match.
 */
bool matrices_are_equal(Matrix *A, Matrix *B);

/**
 * Return the name of the file corresponding to the matrix.
 * @param name the simple matrix name.
 * @return a file name with a matrix extension.
 */
char *get_matrix_file_name(char *name);

#endif //DCU_MATRIX_H
