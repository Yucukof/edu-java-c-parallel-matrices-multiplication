//
// Created by Hadrien BAILLY on 14/03/2022.
//

#include "writer.h"

#define LOCATION "MTX_WRITER"

/**
 * Offload the given matrix to a MTX file on disk.
 * @param matrix the matrix to write.
 * @throw FILE_NOT_FOUND if the file could not be created.
 */
void write_matrix(Matrix *matrix) {

    logger(INFO, LOCATION, "Writing matrix %s to file...", matrix->name);
    char *file_name = get_matrix_file_name(matrix->name);
    File *file = create_file("mtx", file_name);
    open_file(file, WRITE_ONLY);

    FILE *ptr = file->ptr;

    int height = matrix->height;
    int width = matrix->width;
    int **values = matrix->values;
    for (int row = 0; row < height; ++row) {
        if (row > 0) {
            fputc('\n', ptr);
        }
        for (int colum = 0; colum < width; ++colum) {
            if (colum > 0) {
                fputc('\t', ptr);
            }
            fprintf(ptr, "%d", values[row][colum]);
        }
    }
    close_file(file);
    destroy_file(file);

    logger(INFO, LOCATION, "Matrix %s written to file.", matrix->name);
}