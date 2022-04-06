//
// Created by Hadrien BAILLY on 13/03/2022.
//

#ifndef DCU_FILE_UTIL_H
#define DCU_FILE_UTIL_H

#include <stdio.h>
#include <stdbool.h>

#include "../exceptions/exception.h"

/**
 * The various file modes
 */
#define READ_ONLY "r"
#define WRITE_ONLY "wb"
#define READ_WRITE "rw"

/**
 * The structure of a file
 */
typedef struct File {
    FILE *ptr;
    char *path;
    char *name;
    char *mode;
} File;

/**
 * Check if the given file is open.
 * @param file the file to check.
 * @return true if the file is open, false otherwise.
 */
bool file_is_open(File *file);

/**
 * Create a new file
 * @param path the path to the file to open.
 * @param name the name of the file to open.
 * @return a new instance of file.
 */
File *create_file(char *path, char *name);

/**
 * Open the given file in the given mode.
 * @param file the file to open.
 * @param mode the file mode to use.
 * @throw FILE_NOT_FOUND if the file is not found (or any other IO exception).
 */
void open_file(File *file, char *mode);

/**
 * Close the given file.
 * @param file the file to close.
 */
void close_file(File *file);

/**
 * (Close if needed and) destroy the instance of the file
 * @param file the file to destroy.
 */
void destroy_file(File *file);

#endif //DCU_FILE_UTIL_H
