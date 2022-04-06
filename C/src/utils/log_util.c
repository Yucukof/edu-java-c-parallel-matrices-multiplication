//
// Created by Hadrien BAILLY on 12/03/2022.
//

#include "log_util.h"

#define LOG_FORMAT "%s [%s] %-11s: %s\n"
#define LOCATION "LOG_UTIL" // Log location

// Global variables for debugger
/**
 * Pointer to the log file
 */
FILE *f;
/**
 * Status of the logger.
 */
bool isEnabled;
/**
 * Current level of logging.
 */
log_level current_level;

/**
 * The name of the log levels.
 * Must match the log_level enumeration.
 * @see log_level
 * @see get_log_level_name
 */
const char* log_level_value[] = {
        "TRACE",
        "DEBUG",
        "INFO ",
        "WARN ",
        "ERROR",
        "FAIL "
};

/**
 * Open the log file for write.
 */
void open_log() {
    // If logging is enabled, then attempt to open static log file and print first logs
    if (isEnabled) {
        f = fopen("application.log", "w");
        if (f == NULL) {
            logger(FAIL, LOCATION, "File could not be opened!\n");
        }
        logger(INFO, LOCATION, "Log file created.");
    }
}

/**
 * Close the log file.
 */
void close_log() {
    // If log file is available, print last logs and close file
    if (f != NULL) {
        logger(INFO, LOCATION, "Debugger disabled.");
        logger(INFO, LOCATION, "Log file closed.");
        fclose(f);
    }
}

/**
 * Print the given entry to console.
 * @param entry the log entry to print.
 */
void print(Log entry) {
    printf(LOG_FORMAT, entry.time, log_level_value[entry.level], entry.location, entry.msg);
}


/**
 * write the given entry to file.
 * @param entry the log entry to write.
 */
void write(Log entry) {
    if (f != NULL) {
        fprintf(f, LOG_FORMAT, entry.time, log_level_value[entry.level], entry.location, entry.msg);
    } else {
        logger(ERROR, LOCATION, "could not write to file!");
    }
}

/**
 *  Start the logger.
 */
void activate_log() {
    isEnabled = true;
    current_level = INFO;
    open_log();
    logger(INFO, LOCATION, "Logger enabled.");
}

/**
 * Stop the logger.
 */
void deactivate_log() {
    logger(INFO, LOCATION, "Logger disabled.");
    isEnabled = false;
    close_log();
}

/**
 * Update the logger to the given log level.
 * @param new_level the new level to set the logger to.
 */
void set_log_level(log_level new_level) {
    current_level = new_level;
    logger(INFO, LOCATION, "Log level set to %s", log_level_value[current_level]);
}

/**
 * @return the current level value of the logger.
 */
log_level get_log_level() {
    return current_level;
}

/**
 * Parse a log level string into its corresponding enum value.
 * @param level the level to parse
 * @return a log level enumeration value
 */
log_level resolve_level(char *level) {
    for (int index = 0; index <= FAIL; ++index) {
        int distance = strcmp(level, log_level_value[index]);
        if (distance <= 1 && distance >= -1) {
            return index;
        }
    }
    return INFO;
}

/**
 * Record a new log event.
 * @param level the level of the event to record.
 * @param location the location of the event.
 * @param format the format of the message to print.
 * @param ... the variadic arguments to concatenate in the message according to the above format.
 * @see str_util.concatenate
 */
void logger(log_level level, char *location, char *format, ...) {

    if (isEnabled && level >= current_level) {
        va_list vargs;
        va_start(vargs, format);
        char *msg = concatenate(format, vargs);
        va_end(vargs);

        // Get current datetime
        time_t timer;
        time(&timer);
        struct tm *t = localtime(&timer);

        // Extract time value from struct and store it into buffer
        char time[10];
        sprintf(time, "%02i:%02i:%02i", t->tm_hour, t->tm_min, t->tm_sec);

        // Create new log entry with all input and time
        Log entry = {
                .time     = time,
                .level    = level,
                .location = location,
                .msg      = msg,
        };

        // Send log feedback
        print(entry);
        write(entry);

        free(msg);
    }
}