//
// Created by Hadrien BAILLY on 13/03/2022.
//

#include "file_util.h"

#define LOCATION "FILE_UTIL"

/**
 * Check if the given file is open.
 * @param file the file to check.
 * @return true if the file is open, false otherwise.
 */
bool file_is_open(File *file) {
    return file->ptr != NULL;
}

/**
 * Check if the given file is open.
 * @param file the file to check.
 * @return true if the file is open, false otherwise.
 */
File *create_file(char *path, char *name) {
    logger(TRACE, LOCATION, "Creating file for path [%s] and name [%s]", path, name);
    File *file = malloc(sizeof(File));
    file->path = path;
    file->name = name;
    return file;
}

/**
 * Open the given file in the given mode.
 * @param file the file to open.
 * @param mode the file mode to use.
 * @throw FILE_NOT_FOUND if the file is not found (or any other IO exception).
 */
void open_file(File *file, char *mode) {
    char *name = file->name;
    logger(INFO, LOCATION, "Opening file [%s] in %s mode", name, mode);
    char *full_path = concat("%s/%s", file->path, file->name);
    FILE *ptr = fopen(full_path, mode);
    file->ptr = ptr;
    file->mode = mode;
    if (!file_is_open(file)) {
        throw(FILE_NOT_FOUND, LOCATION, "File [%s] not found!", name);
    }
}

/**
 * Close the given file.
 * @param file the file to close.
 */
void close_file(File *file) {
    logger(INFO, LOCATION, "Closing file [%s]", file->name);
    if (file_is_open(file)) {
        FILE *ptr = file->ptr;
        fclose(ptr);
        file->ptr = NULL;
    }
}

/**
 * (Close if needed and) destroy the given file
 * @param file the instance of file to destroy.
 */
void destroy_file(File *file) {
    if (file_is_open(file)) {
        close_file(file);
    }
    free(file->name);
    free(file->ptr);
    free(file);
}