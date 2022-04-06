//
// Created by Hadrien BAILLY on 12/03/2022.
//

#include "exception.h"

#define LOCATION "EXCEPTION"
#define BUFF_SIZE 200

/**
 * The name of the exceptions.
 * Must follow exception_code order
 * @see get_exception_name
 */
char *exception_names[] = {
        "NO_EXCEPTION",
        "EMPTY_MATRIX_ROW",
        "INVALID_MATRIX_DIMENSION",
        "ARG_MATRIX_NAME_MISSING",
        "ARG_MULTIPLICATION_METHOD_MISSING",
        "FILE_NOT_FOUND",
        "ASSERTION_ERROR",
        "CHRONO_NOT_STARTED",
        "CHRONO_NOT_STOPPED",
        "CHRONO_ALREADY_STARTED",
        "CHRONO_ALREADY_STOPPED"
};

/**
 * Return the name associated with an exception code.
 * (similar to that of enum.name() in java)
 * @param code the code of the exception.
 * @return an exception name
 * @see exception_names
 */
char *get_exception_name(exception_code code) {
    return exception_names[code];
}

/**
 * Create a new exception.
 * @param code the code of the exception to create.
 * @param location the location where the exception occurred.
 * @param msg the message describing the exception.
 * @return a new instance of exception.
 */
exception *create_new_exception(exception_code code, char *location, char *msg) {

    exception *e = malloc(sizeof(exception));

    e->code = code;
    e->name = get_exception_name(code);
    e->location = location;
    e->msg = msg;

    return e;
}

/**
 * Generate an exception message and exit program with failure code.
 * @param e the exception to handle.
 */
void handle_exception(exception *e) {
    char output[BUFF_SIZE];
    // @formatter:off
    snprintf(output, BUFF_SIZE, "Exception occurred in %s: %d-%s\nException message: %s"
            , e->location, e->code, e->name, e->msg);
    // @formatter:on
    logger(FAIL, e->location, output);
    exit(EXIT_FAILURE);
}

/**
 * Throw a new exception and interrupt the faulty execution.
 * @param code the code of the exception to throw.
 * @param location the location of the exception.
 * @param format the format of the message, expressed in similar terms of printf
 * @param ... variadic input to print according to the above format.
 */
void throw(exception_code code, char *location, char *format, ...) {

    va_list vargs;
    va_start(vargs, format);
    char *msg = concatenate(format, vargs);
    va_end(vargs);

    exception *e = create_new_exception(code, location, msg);

    handle_exception(e);

}

/**
 * Verify if the given value is true: if not, then throw an exception
 * @param value the value to test for truth.
 * @param location the location of the test.
 * @param message the message to display if test fails.
 */
void assert_true(bool value, char *location, char *message) {
    if (!value)
        throw(ASSERTION_ERROR, location, message);
}