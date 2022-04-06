package org.dcu.student.sem2.ca670.algorithms;

import org.dcu.student.sem2.ca670.matrices.Matrix;

import java.util.function.BiFunction;

/**
 * An interface describing the contract for the implementation of the matrix multiplication.
 *
 * @author Hadrien BAILLY
 */
public interface MatrixMultiplication extends BiFunction<Matrix, Matrix, Matrix> {

    /**
     * Compute the product of two given matrices.
     * @param a the left operand matrix.
     * @param b the right operand matrix.
     * @return a new [x,y] matrix, where x is the height of matrix A, and y the width of matrix B,
     *         containing the result of the dot product multiplications of all vectors in A and B.
     * @throws IllegalArgumentException if the operands matrices dimensions do not match, i.e.
     *          the width of A is not equal to the height of B.
     * @see #canMultiply(Matrix, Matrix)
     */
    default Matrix compute(final Matrix a, final Matrix b) {
        if (canMultiply(a, b)) {
            return apply(a, b);
        }
        throw new IllegalArgumentException("Cannot multiply matrices");
    }

    /**
     * Check if the dimensions of two given matrices matches for multiplication.
     * @param a the left operand matrix.
     * @param b the right operand matrix.
     * @return true if the width of A is equal to the height of B.
     */
    default boolean canMultiply(final Matrix a, final Matrix b) {
        return a.getWidth() == b.getHeight();
    }

}
