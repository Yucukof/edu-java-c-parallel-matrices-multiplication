//
// https://linuxhint.com/gettimeofday_c_language/
// Created by Hadrien BAILLY on 14/03/2022.
//

#include "chrono_util.h"

#define LOCATION "CHRONO_UTIL"

/**
 * Create a new chronometer.
 * @return a new instance of chronometer.
 */
Chrono *create_chrono() {
    logger(INFO, LOCATION, "Creating new chronometer...");

    Chrono *chrono = malloc(sizeof(Chrono));
    chrono->status = READY;

    logger(INFO, LOCATION, "Chronometer created.");
    return chrono;
}

/**
 * Record the time value of the start event.
 * @param chrono the chronometer to record the event.
 */
void start_chrono(Chrono *chrono) {

    logger(INFO, LOCATION, "Starting chronometer...");

    if (chrono->status != READY) {
        throw(CHRONO_ALREADY_STARTED, LOCATION, "Chronometer was already started!");
    }

    gettimeofday(&chrono->start, NULL);
    chrono->status = STARTED;

    logger(INFO, LOCATION, "Chronometer started.");
}

/**
 * Record the time value of the stop event.
 * @param chrono the chronometer to record the event.
 */
void stop_chrono(Chrono *chrono) {
    logger(INFO, LOCATION, "Stopping chronometer...");

    if (chrono->status == READY) {
        throw(CHRONO_NOT_STARTED, LOCATION, "Chronometer was not started!");
    }

    if (chrono->status == STOPPED) {
        throw(CHRONO_ALREADY_STOPPED, LOCATION, "Chronometer was already stopped!");
    }

    gettimeofday(&chrono->stop, NULL);
    chrono->status = STOPPED;

    logger(INFO, LOCATION, "Chronometer stopped.");

    show_duration(chrono);
}

/**
 * Destroy the given chronometer.
 * @param chrono the instance of chronometer to destroy.
 */
void destroy_chrono(Chrono *chrono) {
    logger(INFO, LOCATION, "Destroying chronometer...");

    free(chrono);

    logger(INFO, LOCATION, "Chronometer destroyed.");
}

/**
 * Get the time elapsed in the chronometer.
 * @param chrono the chronometer to get duration from.
 * @return a duration in milliseconds, with a precision up to nanoseconds.
 */
long double get_duration(Chrono *chrono) {
    if (chrono->status != STOPPED){
        throw(CHRONO_NOT_STOPPED,LOCATION,"Chronometer was not stopped!");
    }
    long int start = chrono->start.tv_sec * 1000000 + chrono->start.tv_usec;
    long int stop = chrono->stop.tv_sec * 1000000 + chrono->stop.tv_usec;
    return ((long double) (stop - start))/1000;
}

/**
 * Record the current duration in a log entry.
 * @param chrono the chronometer from which obtain the duration.
 */
void show_duration(Chrono *chrono) {
    long double duration = get_duration(chrono);

    char time_str[10];
    snprintf(time_str, sizeof time_str, "%'1.3Lf", duration);
    logger(WARN, LOCATION, "Duration: %s ms.", time_str);
}
