//
// https://www.cplusplus.com/reference/cstring/strtok/
// Created by Hadrien BAILLY on 11/03/2022.
//

#include "loader.h"

#define LOCATION "MTX_LOADER"

/**
 * Count the number of columns in a given line, in order to estimate a matrix's width.
 * @param file the file to count the number of columns.
 * @param matrix the matrix to dimension.
 */
void count_column(Matrix *matrix, char *line, int line_number) {
    logger(DEBUG, LOCATION, "Measuring line %d...", line_number);
    int width = 0;
    char *cells = strtok(line, " \t\n");
    while (cells) {
        width++;
        cells = strtok(NULL, " \t\n");
    }
    logger(DEBUG, LOCATION, "Width of line %d = %d", line_number, width);

    if (matrix->width < width) {
        logger(DEBUG, LOCATION, "Matrix's width updated from %d to %d.", matrix->width, width);
        matrix->width = width;
    }
}

/**
 * Count the number of rows and columns in a given file, in order to estimate a matrix's height and width.
 * @param file the file to count the number of lines and length.
 * @param matrix the matrix to dimension.
 */
void count_row(File *file, Matrix *matrix) {
    FILE *ptr = file->ptr;
    char line[MAX_LINE_LENGTH];
    int height = 0;
    while (fgets(line, MAX_LINE_LENGTH, ptr)) {
        if (strlen(line) > 0) {
            count_column(matrix, line, height);
            height++;
        }
    }
    matrix->height = height;
}


/**
 * Process each column from a row from the given file in order to fill matrix's data.
 * @param file the file to read data from.
 * @param matrix the matrix to write data to.
 * @throw INVALID_MATRIX_DIMENSION if the number of columns read does not match the matrix width.
 */
void fill_columns(Matrix *matrix, char *line, int line_number) {

    logger(DEBUG, LOCATION, "Processing columns for line %d...", line_number);

    char *cells;
    int column_number = 0;
    int **values = matrix->values;

    // Read first cell
    cells = strtok(line, " \t\n");
    // Increment cursor
    // While cell is not end of the line, process cell
    while (cells) {
        // Parse integer value from cell
        int value = atoi(cells);
        logger(TRACE, LOCATION, "[%d, %d] = %d", line_number, column_number, value);
        // Store value in row
        values[line_number][column_number] = value;
        // Increment cursor value
        cells = strtok(NULL, " \t\n");
        // Increment counter
        column_number++;
    }
    if (matrix->width != column_number) {
        throw(INVALID_MATRIX_DIMENSION, LOCATION, "Invalid number of columns on row %s: expected %d - found %d",
              matrix->width, column_number);
    }
    logger(DEBUG, LOCATION, "%d columns processed.", column_number);
}

/**
 * Process each row and column from the given file in order to fill matrix's data.
 * @param file the file to read data from.
 * @param matrix the matrix to write data to.
 * @throw INVALID_MATRIX_DIMENSION if the number of rows read does not match the matrix height.
 *        or the number of columns read does not match the matrix width.
 */
void fill_rows(File *file, Matrix *matrix) {

    logger(INFO, LOCATION, "Copying matrix's file content...");

    FILE *ptr = file->ptr;
    int row_number = 0;
    char line[MAX_LINE_LENGTH];
    logger(DEBUG, LOCATION, "Processing lines...");
    while (fgets(line, MAX_LINE_LENGTH, ptr)) {
        if (strlen(line) > 0) {
            fill_columns(matrix, line, row_number);
            row_number++;
        }
    }
    if (matrix->height != row_number) {
        throw(INVALID_MATRIX_DIMENSION, LOCATION, "Invalid number of rows: Expected %d - found %d",
              matrix->height, row_number);
    }

    logger(DEBUG, LOCATION, "%d lines processed.", row_number);

    logger(INFO, LOCATION, "Matrix's file content copied.");
}

/**
 * Estimate the memory to be allocated in order to load the matrix from the given file.
 * @param file the file from which estimate the needs.
 * @param matrix the matrix to allocate.
 * @throw FILE_NOT_FOUND if the file is not found (or any other IO exception).
 */
void estimate(File *file, Matrix *matrix) {

    logger(INFO, LOCATION, "Estimating memory needs for file [%s]...", file->name);

    open_file(file, READ_ONLY);
    count_row(file, matrix);
    close_file(file);

    int height = matrix->height;
    int width = matrix->width;

    logger(INFO, LOCATION, "Estimated needs: [%d,%d].", height, width);
}

/**
 * Fill the matrix memory with the content of the given file.
 * @param file the file to read the content from.
 * @param matrix the matrix to fill.
 * @throw FILE_NOT_FOUND if the file is not found (or any other IO exception).
 */
void fill(File *file, Matrix *matrix) {
    logger(INFO, LOCATION, "Filling [%d,%d] matrix from file [%s]...", matrix->height, matrix->width, file->name);
    open_file(file, READ_ONLY);
    fill_rows(file, matrix);
    close_file(file);
    logger(INFO, LOCATION, "Matrix filled.");
}

/**
 * Load a given matrix from a MTX file into memory.
 * @param matrix_name the name of the matrix to load.
 * @return a new instance of matrix.
 * @throw INVALID_MATRIX_DIMENSION if the matrix contained in the file is not valid
 *        (any null dimensions/inconsistent row length)
 * @throw FILE_NOT_FOUND if the file is not found (or any other IO exception).
 */
Matrix *load_matrix(char *matrix_name) {
    logger(INFO, LOCATION, "Loading new matrix [%s]...", matrix_name);

    char *file_name = get_matrix_file_name(matrix_name);
    Matrix *matrix = create_empty_matrix(matrix_name);
    File *file = create_file("mtx", file_name);

    estimate(file, matrix);
    allocate_memory(matrix);
    fill(file, matrix);

    if (get_log_level() == DEBUG) {
        display_matrix(matrix);
    }

    logger(INFO, LOCATION, "Matrix loaded");
    return matrix;
}