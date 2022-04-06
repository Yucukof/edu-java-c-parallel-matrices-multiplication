//
// Created by Hadrien BAILLY on 11/03/2022.
//

#ifndef DCU_MAIN_H
#define DCU_MAIN_H

#include <locale.h>

#include "utils/log_util.h"
#include "matrices/loader.h"
#include "matrices/matrix.h"
#include "matrices/writer.h"
#include "matrices/multiply.h"
#include "exceptions/exception.h"

/**
 * The main function of the C matrix multiplication program.
 * It takes two required arguments and one optional:
 * @param name the name of the matrix group to test.
 * @param algo the algorithm to use.
 *        0 for sequential processing, 1 for parallel
 * @param log_level the log level to display (optional)
 */
int main(int argc, char *argv[]);

#endif //DCU_MAIN_H
