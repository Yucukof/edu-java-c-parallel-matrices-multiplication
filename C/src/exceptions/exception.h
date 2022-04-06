//
// https://web.archive.org/web/20091104065428/http://www.di.unipi.it/~nids/docs/longjump_try_trow_catch.html
// Created by Hadrien Bailly on 12/03/2022.
//

#ifndef DCU_EXCEPTION_H
#define DCU_EXCEPTION_H "exception.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../utils/str_util.h"
#include "../utils/log_util.h"

/**
 * The possible exceptions identified.
 */
typedef enum exception_code {
    NO_EXCEPTION,
    EMPTY_MATRIX_ROW,
    INVALID_MATRIX_DIMENSION,
    ARG_MATRIX_NAME_MISSING,
    ARG_MULTIPLICATION_METHOD_MISSING,
    FILE_NOT_FOUND,
    ASSERTION_ERROR,
    CHRONO_NOT_STARTED,
    CHRONO_NOT_STOPPED,
    CHRONO_ALREADY_STARTED,
    CHRONO_ALREADY_STOPPED
} exception_code;

/**
 * The structure of an exception
 */
typedef struct exception {
    exception_code code;
    char *name;
    char *location;
    char *msg;
} exception;


/**
 * Throw a new exception and interrupt the faulty execution.
 * @param code the code of the exception to throw.
 * @param location the location of the exception.
 * @param format the format of the message, expressed in similar terms of printf
 * @param ... variadic input to print according to the above format.
 */
//@formatter:off
void throw(exception_code code, char *location, char *format, ...);
//@formatter:on

/**
 * Verify if the given value is true: if not, then throw an exception
 * @param value the value to test for truth.
 * @param location the location of the test.
 * @param message the message to display if test fails.
 */
void assert_true(bool value, char *location, char *message);

#endif //DCU_EXCEPTION_H
