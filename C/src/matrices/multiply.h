//
// Created by Hadrien BAILLY on 13/03/2022.
//

#ifndef DCU_MTX_MULTIPLICATION_H
#define DCU_MTX_MULTIPLICATION_H

#include "matrix.h"

#include "../utils/chrono_util.h"

/**
 * Multiply two matrices using a plain sequential algorithm.
 * @param A the left operand matrix.
 * @param B the right operand matrix.
 * @return a new instance of matrix of dimension [A.height, B.width]
 *         containing the dot product of all vectors.
 * @throw INVALID_MATRIX_DIMENSION if the matrices cannot be multiplied
 *        because A.width is not equal to B.height.
 */
Matrix *multiply_sequential(Matrix *A, Matrix *B);

/**
 * Multiply two matrices using a stripe parallel algorithm.
 * @param A the left operand matrix.
 * @param B the right operand matrix.
 * @return a new instance of matrix of dimension [A.height, B.width]
 *         containing the dot product of all vectors.
 * @throw INVALID_MATRIX_DIMENSION if the matrices cannot be multiplied
 *        because A.width is not equal to B.height.
 */
Matrix *multiply_parallel(Matrix *A, Matrix *B);

#endif //DCU_MTX_MULTIPLICATION_H
