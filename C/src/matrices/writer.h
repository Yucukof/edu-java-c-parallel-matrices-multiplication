//
// Created by Hadrien BAILLY on 14/03/2022.
//

#ifndef DCU_WRITER_H
#define DCU_WRITER_H

#include "matrix.h"

#include "../utils/file_util.h"
#include "../utils/log_util.h"

/**
 * Offload the given matrix to a MTX file on disk.
 * @param matrix the matrix to write.
 * @throw FILE_NOT_FOUND if the file could not be created.
 */
void write_matrix(Matrix *matrix);

#endif //DCU_WRITER_H
