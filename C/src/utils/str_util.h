//
// Created by Hadrien BAILLY on 12/03/2022.
//

#ifndef DCU_STR_UTIL_H
#define DCU_STR_UTIL_H

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>

#define BUFFER_SIZE 200

/**
 * Concatenate the variadic arguments into a single string according to a given format.
 * @param format the format to follow.
 * @param ... the variadic arguments.
 * @return a concatenate string.
 */
char *concat(char *format, ...);

/**
 * Concatenate the variadic arguments into a single string according to a given format.
 * @param format the format to follow.
 * @param vargs the variadic arguments.
 * @return a concatenate string.
 */
char *concatenate(char *format, va_list vargs);

#endif //DCU_STR_UTIL_H
