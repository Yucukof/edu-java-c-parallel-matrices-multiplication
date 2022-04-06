//
// Created by Hadrien BAILLY on 12/03/2022.
//

#ifndef DCU_LOG_UTIL_H
#define DCU_LOG_UTIL_H "log_util.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>

#include "str_util.h"

#include "../exceptions/exception.h"

/**
 * The list of log level identified.
 */
typedef enum log_level {
    TRACE,
    DEBUG,
    INFO,
    WARN,
    ERROR,
    FAIL
} log_level;

/**
 * The structure of a log entry
 */
typedef struct Log {
    char *time;
    log_level level;
    char *location;
    char *msg;
} Log;

/**
 *  Start the logger.
 */
void activate_log();

/**
 * Stop the logger.
 */
void deactivate_log();

/**
 * Update the logger to the given log level.
 * @param new_level the new level to set the logger to.
 */
void set_log_level(log_level new_level);

/**
 * @return the current level value of the logger.
 */
log_level get_log_level();

/**
 * Parse a log level string into its corresponding enum value.
 * @param level the level to parse
 * @return a log level enumeration value
 */
log_level resolve_level(char *level);

/**
 * Record a new log event.
 * @param level the level of the event to record.
 * @param location the location of the event.
 * @param format the format of the message to print.
 * @param ... the variadic arguments to concatenate in the message according to the above format.
 * @see str_util.concatenate
 */
void logger(log_level level, char location[], char *format, ...);

#endif //DCU_LOG_UTIL_H