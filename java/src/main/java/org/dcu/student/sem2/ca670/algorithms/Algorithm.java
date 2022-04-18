package org.dcu.student.sem2.ca670.algorithms;

import lombok.AccessLevel;
import lombok.NoArgsConstructor;
import lombok.RequiredArgsConstructor;
import org.dcu.student.sem2.ca670.matrices.Matrix;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

/**
 * An enumeration presenting the different implementations of the matrix multiplication.
 *
 * @author Hadrien BAILLY
 */
@RequiredArgsConstructor
public enum Algorithm {
    /**
     * The sequential algorithm.
     */
    SEQUENTIAL("Sequential", new SequentialMatrixMultiplication()),
    /**
     * The simple parallel algorithm computing stripes concurrently.
     */
    STRIPE("Parallel Striping", new ParallelStripeMatrixMultiplication()),
    /**
     * The deeper parallel algorithm computing multiplication concurrently and addition consequently.
     */
    REDUCE("Parallel Reduction", new ParallelReduceMatrixMultiplication()),
    /**
     * A revised version of the simple parallel algorithm computing stripes concurrently, using Java Streams.
     */
    FORK_JOIN("Java Fork/Join parallelism", new ParallelForkJoinMatrixMultiplication()),
    /**
     * A revised version of the simple parallel algorithm computing stripes concurrently, using Java Streams.
     */
    STREAM("Java Streams parallelism", new ParallelStreamMatrixMultiplication());

    /**
     * The short name for the multiplication algorithm.
     */
    private final String name;
    /**
     * An instance of the multiplication algorithm.
     */
    public final MatrixMultiplication implementation;

    /**
     *
     * @return the name of the algorithm
     */
    public String getName() {
        return name;
    }

    /**
     * Execute a matrix multiplication following the current algorithm implementation.
     * @param a the left operand matrix.
     * @param b the right operand matrix.
     * @return a product matrix.
     */
    public Matrix multiply(final Matrix a, final Matrix b) {
        Logging.log.info("Computing product of {} and {}...", a.getName(), b.getName());
        return implementation.compute(a, b);
    }
}

/**
 * A utility class holding a private logger for the interface.
 */
@NoArgsConstructor(access = AccessLevel.PRIVATE)
final class Logging {

    /**
     * The private logger for the interface.
     */
    static final Logger log = LoggerFactory.getLogger(Algorithm.class);

}

