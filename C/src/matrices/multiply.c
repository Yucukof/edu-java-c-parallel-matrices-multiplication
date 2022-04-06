//
// Created by Hadrien BAILLY on 13/03/2022.
//

#include "multiply.h"

#define LOCATION "MTX_MULTI"

/**
 * Verify that the two matrices can be multiplied, i.e. that A.width is equal to B.height.
 * @param A the left operand matrix.
 * @param B the right operand matrix.
 * @throw INVALID_MATRIX_DIMENSION if A.width is not equal to B.height.
 */
void check_dimensions(Matrix *A, Matrix *B) {
    if (A->width != B->height) {
        throw(INVALID_MATRIX_DIMENSION, LOCATION, "Matrix %s [%d,%d] cannot be multiplied with matrix %s [%d,%d]",
              A->name, A->height, A->width, B->name, B->height, B->width);
    }
}

/**
 * Process all multiplication operations concurrently, then perform additions in a reduction.
 * @param product the product matrix to write results to.
 * @param A the left operand matrix.
 * @param B the right operand matrix.
 * @param row the row number of the stripe.
 * @param column the column number of the stripe.
 */
void process_stripe_parallel(Matrix *product, Matrix *A, Matrix *B, int row, int column) {
    int sum = 0;
    #pragma omp parallel for reduction (+:sum)
    for (int stripe = 0; stripe < A->width; stripe++) {
        sum += A->values[row][stripe] * B->values[stripe][column];
    }
    product->values[row][column] = sum;
}

/**
 * Multiply two matrices using a stripe parallel algorithm.
 * @param A the left operand matrix.
 * @param B the right operand matrix.
 * @return a new instance of matrix of dimension [A.height, B.width]
 *         containing the dot product of all vectors.
 * @throw INVALID_MATRIX_DIMENSION if the matrices cannot be multiplied
 *        because A.width is not equal to B.height.
 */
Matrix *multiply_parallel(Matrix *A, Matrix *B) {

    check_dimensions(A, B);

    Chrono *chrono = create_chrono();
    start_chrono(chrono);

    Matrix *C = create_matrix(concat("%sx%s", A->name, B->name), A->height, B->width);

    #pragma omp parallel for
    for (int row = 0; row < A->height; ++row) {

    #pragma omp parallel for
        for (int column = 0; column < B->width; ++column) {
            process_stripe_parallel(C, A, B, row, column);
        }
    }
    stop_chrono(chrono);
    if (get_log_level() == DEBUG) {
        display_matrix(C);
    }
    return C;
}

/**
 * Multiply two matrices using a plain sequential algorithm.
 * @param A the left operand matrix.
 * @param B the right operand matrix.
 * @return a new instance of matrix of dimension [A.height, B.width]
 *         containing the dot product of all vectors.
 * @throw INVALID_MATRIX_DIMENSION if the matrices cannot be multiplied
 *        because A.width is not equal to B.height.
 */
Matrix *multiply_sequential(Matrix *A, Matrix *B) {

    check_dimensions(A, B);

    Chrono *chrono = create_chrono();
    start_chrono(chrono);

    Matrix *product = create_matrix(concat("%sx%s", A->name, B->name), A->height, B->width);
    int **values = product->values;

    for (int row = 0; row < A->height; ++row) {
        for (int column = 0; column < B->width; ++column) {
            values[row][column] = 0;
            for (int stripe = 0; stripe < A->width; stripe++) {
                values[row][column] += A->values[row][stripe] * B->values[stripe][column];
            }
        }
    }
    stop_chrono(chrono);
    if (get_log_level() == DEBUG) {
        display_matrix(product);
    }
    return product;
}

