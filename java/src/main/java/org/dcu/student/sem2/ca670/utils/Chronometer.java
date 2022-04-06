package org.dcu.student.sem2.ca670.utils;

import lombok.Data;
import lombok.extern.slf4j.Slf4j;

import java.time.Duration;
import java.time.Instant;
import java.time.temporal.ChronoUnit;

/**
 * A utility class for estimating the duration between two events in microseconds.
 * <br>
 * Freely inspired from <a href=http://silveiraneto.net/2008/03/15/simple-java-chronometer/>A Simple Java Chronometer by Silveira Neto</a>
 * @author Hadrien BAILLY.
 */
@Slf4j
@Data
public class Chronometer {

    /**
     * The instant upon which occurred the first event.
     */
    private Instant start;
    /**
     * The instant upon which occured the second event.
     */
    private Instant end;

    /**
     * A default constructor with some logging
     */
    public Chronometer() {
        log.info("Creating new chronometer...");
        log.info("Chronometer created.");
    }

    /**
     *
     * @return the duration in microseconds between the two events.
     * @throws IllegalStateException when the chronometer was not started nor stopped.
     */
    public double getDuration() {
        log.debug("Getting duration...");

        // Check if the chronometer state is valid
        if (start == null) {
            throw new IllegalStateException("Chronometer was not started!");
        }
        if (end == null) {
            throw new IllegalStateException("Chronometer was not stopped!");
        }

        final Duration duration = Duration.between(start, end);

        final double seconds = (0F + duration.getSeconds()) * 1000;
        final double milli = (0F + duration.getNano()) / 1000000;

        return seconds + milli;
    }

    /**
     * Start the chronometer and record the instant of the first event.
     * @throws IllegalStateException when the chronometer is already started.
     */
    public void start() {
        log.info("Starting chronometer...");

        // Check if the chronometer state is valid
        if (start != null) {
            throw new IllegalStateException("Chronometer was already started!");
        }

        start = getMicroInstant();
        log.info("Chronometer started.");
    }

    private Instant getMicroInstant() {
        return Instant.now().truncatedTo(ChronoUnit.MICROS);
    }

    /**
     * Stop the chronometer and record the instant of the second event.
     * @throws IllegalStateException when the chronometer is not started or already stopped.
     */
    public void stop() {
        log.info("Stopping chronometer...");

        // Check if the chronometer state is valid
        if (start == null) {
            throw new IllegalStateException("Chronometer was not started!");
        }
        if (end != null) {
            throw new IllegalStateException("Chronometer was already stopped!");
        }

        end = getMicroInstant();
        log.info("Chronometer stopped.");
    }

}