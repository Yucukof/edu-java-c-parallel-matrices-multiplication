//
// Created by Hadrien BAILLY on 11/03/2022.
//

#include "matrix.h"

#define LOCATION "MATRIX"

/**
 * Return a new matrix.
 * @param name the name of the matrix to instantiate.
 * @return a new matrix instance.
 */
Matrix *create_empty_matrix(char *name) {

    logger(INFO, LOCATION, "Creating empty matrix...", 0, 0);

    Matrix *matrix = malloc(sizeof(Matrix));

    matrix->name = name;
    matrix->height = 0;
    matrix->width = 0;

    return matrix;
}

/**
 * Allocate heap memory to a given matrix
 * @param matrix the matrix for which allocate memory.
 * @throw INVALID_MATRIX_DIMENSION if the matrix has any dimension equal to 0.
 */
void allocate_memory(Matrix *matrix) {

    logger(INFO, LOCATION, "Allocating memory for [%d,%d] matrix...", matrix->height, matrix->width);

    int height = matrix->height;
    int width = matrix->width;

    if (height == 0 || width == 0)
        throw(INVALID_MATRIX_DIMENSION, LOCATION, "Cannot allocate memory to a [%d,%d] matrix", height, width);

    matrix->values = malloc(sizeof(int *) * height);

    int **values = matrix->values;
    for (int row = 0; row < height; ++row) {
        values[row] = malloc(sizeof(int) * width);
    }

    logger(INFO, LOCATION, "Memory allocated.", height, width);
}

/**
 * Returns a new matrix with allocated memory.
 * @param name the name of the matrix to create.
 * @param height the height of the matrix to create.
 * @param width the width of the matrix to create.
 * @return a new instance of a matrix with a [height,width] heap memory allocation.
 * @throw INVALID_MATRIX_DIMENSION if the matrix has any dimension equal to 0.
 */
Matrix *create_matrix(char *name, unsigned int height, unsigned int width) {

    logger(INFO, LOCATION, "Creating new [%d,%d] matrix...", height, width);

    Matrix *matrix = create_empty_matrix(name);
    matrix->height = height;
    matrix->width = width;

    allocate_memory(matrix);

    return matrix;
}

/**
 * Free and remove the given matrix from the heap.
 * @param matrix the matrix to destroy.
 */
void destroy_matrix(Matrix *matrix) {
    logger(INFO, LOCATION, "Destroying matrix [%s]...", matrix->name);
    int height = matrix->height;
    int **values = matrix->values;
    for (int row = 0; row < height; ++row) {
        free(values[row]);
    }
    free(values);
    free(matrix);
}

/**
 * Display the given matrix on screen.
 * @param matrix the matrix to display.
 */
void display_matrix(Matrix *matrix) {
    logger(DEBUG, LOCATION, "Displaying matrix...");

    int height = matrix->height;
    int width = matrix->width;
    int **values = matrix->values;

    for (int row = 0; row < height; ++row) {
        for (int column = 0; column < width; ++column) {
            if (column > 0) {
                printf("\t");
            }
            printf("%3d", values[row][column]);
        }
        printf("\n");
    }
}

/**
 * Check if two matrices are equal re. their data.
 * @param A the first matrix to compare.
 * @param B the second matrix to compare.
 * @return true if both matrices contain the same values.
 * @throw INVALID_MATRIX_DIMENSION if the matrices' dimensions do not match.
 */
bool matrices_are_equal(Matrix *A, Matrix *B) {

    logger(INFO, LOCATION, "Comparing matrix [%s] with matrix [%s]", A->name, B->name);

    int height = A->height;
    int width = A->width;
    if (B->height != height || B->width != width) {
        throw(INVALID_MATRIX_DIMENSION, LOCATION, "Matrix %s [%d,%d] cannot match with matrix %s [%d,%d]",
              A->name, height, width, B->name, B->height, B->width);
    }

    int **a = A->values;
    int **b = B->values;
    for (int row = 0; row < height; ++row) {
        for (int column = 0; column < width; ++column) {
            if (a[row][column] != b[row][column]) {
                logger(INFO, LOCATION, "On [%d,%d], matrix [%s] (%d) does not match with matrix [%s] (%d)", row, column,
                       A->name, a[row][column], B->name, b[row][column]);
                return false;
            }
        }
    }
    return true;
}

/**
 * Return the name of the file corresponding to the matrix.
 * @param name the simple matrix name.
 * @return a file name with a matrix extension.
 */
char *get_matrix_file_name(char *name) {
    return concat("%s.%s", name, MATRIX_FILE_EXT);
}
