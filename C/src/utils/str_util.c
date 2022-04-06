//
// https://en.cppreference.com/w/c/variadic
// Created by Hadrien BAILLY on 12/03/2022.
//

#include "str_util.h"

#define LOCATION "STR_UTIL"

/**
 * Parse and concatenate the given argument as an int.
 * @param vargs the argument to parse
 * @param output the string where to append the parsed argument.
 */
void parse_int(va_list vargs, char *output) {
    char str_i[10];
    int i = va_arg(vargs,
    int);
    snprintf(str_i, 10, "%d", i);
    strncat(output, str_i, BUFFER_SIZE);
}

/**
 * Parse and concatenate the given argument as a float.
 * @param vargs the argument to parse
 * @param output the string where to append the parsed argument.
 */
void parse_float(va_list vargs, char *output) {
    char str_f[10];
    double f = va_arg(vargs,
    double);
    snprintf(str_f, 10, "%f", f);
    strncat(output, str_f, BUFFER_SIZE);
}

/**
 * Parse and concatenate the given argument as a char.
 * @param vargs the argument to parse
 * @param output the string where to append the parsed argument.
 */
void parse_char(va_list vargs, char *output) {
    int c = va_arg(vargs,
    int);
    char str_c[2];
    snprintf(str_c, 2, "%c", c);
    strncat(output, str_c, BUFFER_SIZE);
}

/**
 * Parse and concatenate the given argument as pointer.
 * @param vargs the argument to parse
 * @param output the string where to append the parsed argument.
 */
void parse_ptr(va_list vargs, char *output) {
    void *ptr = va_arg(vargs,
    void *);
    char str_ptr[16];
    snprintf(str_ptr, 15, "%p", ptr);
    strncat(output, str_ptr, BUFFER_SIZE);
}

/**
 * Parse and concatenate the given argument as a string.
 * @param vargs the argument to parse
 * @param output the string where to append the parsed argument.
 */
void parse_str(va_list vargs, char *output) {
    char *str_c = va_arg(vargs,
    char*);
    strncat(output, str_c, BUFFER_SIZE);
}

/**
 * Concatenate the variadic arguments into a single string according to a given format.
 * @param format the format to follow.
 * @param vargs the variadic arguments.
 * @return a concatenate string.
 */
char *concatenate(char *format, va_list vargs) {
    char *output = malloc(sizeof(char) * BUFFER_SIZE);
    output[0] = '\0';

    while (*format != '\0') {
        if (*format == '%') {
            switch (*++format) {
                case 'c':
                    parse_char(vargs, output);
                    break;
                case 'i':
                case 'd':
                    parse_int(vargs, output);
                    break;
                case 'f':
                    parse_float(vargs, output);
                    break;
                case 'p':
                    parse_ptr(vargs, output);
                    break;
                case 's':
                    parse_str(vargs, output);
                    break;
                default:
                    printf("Unknown formatter: %c\n", *format);
            }
        } else {
            strncat(output, format, 1);
        }
        ++format;
    }
    return output;
}

/**
 * Concatenate the variadic arguments into a single string according to a given format.
 * @param format the format to follow.
 * @param ... the variadic arguments.
 * @return a concatenate string.
 */
char *concat(char *format, ...) {

    va_list vargs;
    va_start(vargs, format);

    char *output = concatenate(format, vargs);
    va_end(vargs);
    return output;
}