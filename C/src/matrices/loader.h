//
// Created by Hadrien BAILLY on 11/03/2022.
//

#ifndef DCU_MTX_LOADER_H
#define DCU_MTX_LOADER_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "matrix.h"
#include "../exceptions/exception.h"

#include "../utils/log_util.h"
#include "../utils/str_util.h"
#include "../utils/file_util.h"

#define MAX_LINE_LENGTH 20000

/**
 * Load a given matrix from a MTX file into memory.
 * @param matrix_name the name of the matrix to load.
 * @return a new instance of matrix.
 * @throw INVALID_MATRIX_DIMENSION if the matrix contained in the file is not valid
 *        (any null dimensions/inconsistent row length)
 * @throw FILE_NOT_FOUND if the file is not found (or any other IO exception).
 */
Matrix *load_matrix(char *matrix_name);

#endif //DCU_MTX_LOADER_H
