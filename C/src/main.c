//
// Created by Hadrien BAILLY on 11/03/2022.
//

#include "main.h"

#define LOCATION "MAIN"

/**
 * The launcher test method.
 * @param name the name of the matrices group.
 * @param A the left operand matrix.
 * @param B the right operand matrix.
 * @param C the expected resulting matrix.
 * @param function the matrix multiplication algorithm function to use.
 * @param test the name of the test.
 */
void test_function(char *name, Matrix *A, Matrix *B, Matrix *C, Matrix *(*function)(Matrix *, Matrix *), char *test) {

    logger(INFO, LOCATION, "Computing product of %sA and %sB...", name, name);

    logger(INFO, LOCATION, "Using %s method...", test);
    Matrix *productAB = function(A, B);
    write_matrix(productAB);

    logger(INFO, LOCATION, "Asserting computation is correct...");
    assert_true(matrices_are_equal(C, productAB), LOCATION,
                concat("Product of %sA and %sB does not match %sC", name, name, name));

    logger(INFO, LOCATION, "Product of %sA and %sB is correct!", name, name);

    destroy_matrix(productAB);
}

/**
 * The main test method.
 * @param name the anme of the matrices to use for the test.
 * @param algo the matrix multiplication algorithm to use.
 */
void test(char *name, int algo) {

    logger(INFO, LOCATION, "Performing Matrices Multiplication Test...");
    logger(INFO, LOCATION, "Selected matrices group: %s", name);

    logger(INFO, LOCATION, "Setting-up...");
    Matrix *A = load_matrix(concat("%s%s", name, "A"));
    Matrix *B = load_matrix(concat("%s%s", name, "B"));
    Matrix *C = load_matrix(concat("%s%s", name, "C"));

    if (algo) {
        test_function(name, A, B, C, multiply_parallel, "parallel");
    } else {
        test_function(name, A, B, C, multiply_sequential, "sequential");
    }

    logger(INFO, LOCATION, "Cleaning-up...");

    destroy_matrix(A);
    destroy_matrix(B);
    destroy_matrix(C);

    logger(INFO, LOCATION, "Test completed");
}

/**
 * The main function of the C matrix multiplication program.
 * It takes two required arguments and one optional:
 * @param name the name of the matrix group to test.
 * @param algo the algorithm to use.
 *        0 for sequential processing, 1 for parallel
 * @param log_level the log level to display (optional)
 */
int main(int argc, char *argv[]) {

    activate_log();
    resolve_level("INFO ");

    if (argc >= 4) {
        set_log_level(resolve_level(argv[3]));
    }

    if (argc < 2) {
        throw(ARG_MATRIX_NAME_MISSING, LOCATION, "Matrix group name argument was not supplied!");
    }

    if (argc < 3) {
        throw(ARG_MULTIPLICATION_METHOD_MISSING, LOCATION, "Multiplication method argument was not supplied!");
    }

    test(argv[1], atoi(argv[2]));

    deactivate_log();

    return EXIT_SUCCESS;

}