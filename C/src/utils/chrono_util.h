//
// Created by Hadrien BAILLY on 14/03/2022.
//

#ifndef DCU_CHRONO_UTIL_H
#define DCU_CHRONO_UTIL_H

#include <unistd.h>
#include <stdio.h>
#include <sys/time.h>

#include "log_util.h"

#include "../exceptions/exception.h"

/**
 * The identified list of status.
 */
typedef enum chrono_status {
    READY,
    STARTED,
    STOPPED
} chrono_status;

/**
 * The structure of a chronometer
 */
typedef struct Chrono {

    chrono_status status;

    struct timeval start;
    struct timeval stop;

} Chrono;

/**
 * Create a new chronometer.
 * @return a new instance of chronometer.
 */
Chrono *create_chrono();

/**
 * Record the time value of the start event.
 * @param chrono the chronometer to record the event.
 */
void start_chrono(Chrono *chrono);

/**
 * Record the time value of the stop event.
 * @param chrono the chronometer to record the event.
 */
void stop_chrono(Chrono *chrono);

/**
 * Destroy the given chronometer.
 * @param chrono the instance of chronometer to destroy.
 */
void destroy_chrono(Chrono *chrono);

/**
 * Get the time elapsed in the chronometer.
 * @param chrono the chronometer to get duration from.
 * @return a duration in milliseconds, with a precision up to nanoseconds.
 */
long double get_duration(Chrono *chrono);

/**
 * Record the current duration in a log entry.
 * @param chrono the chronometer from which obtain the duration.
 */
void show_duration(Chrono *chrono);

#endif //DCU_CHRONO_UTIL_H
