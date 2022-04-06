package org.dcu.student.sem2.ca670.algorithms;

import lombok.Getter;
import lombok.extern.slf4j.Slf4j;
import org.dcu.student.sem2.ca670.matrices.Matrix;
import org.dcu.student.sem2.ca670.utils.Chronometer;

import java.util.stream.IntStream;

@Slf4j
public class ParallelStreamMatrixMultiplication implements MatrixMultiplication {

    @Override
    public Matrix apply(final Matrix matrixA, final Matrix matrixB) {
        log.info("Using {} method...", Algorithm.REDUCE.getName());
        final Context context = new Context(matrixA, matrixB);
        return context.execute();
    }

    @Getter
    private static final class Context {

        private final Matrix matrixA;
        private final Matrix matrixB;

        private final int height;
        private final int width;
        private final int dimension;

        private final Matrix matrix;
        private final int[][] values;

        private final Chronometer chronometer = new Chronometer();

        public Context(final Matrix matrixA, final Matrix matrixB) {
            log.info("Creating context...");

            this.matrixA = matrixA;
            this.matrixB = matrixB;

            this.height = matrixA.getHeight();
            this.width = matrixB.getWidth();
            this.dimension = matrixA.getWidth();

            final String name = matrixA.getName() + "x" + matrixB.getName();
            final Matrix product = new Matrix(name);
            product.allocate(new int[height][width]);

            this.matrix = product;
            this.values = product.getValues();

            log.info("Context created.");
        }

        public Matrix execute() {
            log.info("Executing multiplication...");
            chronometer.start();
            IntStream.range(0, dimension)
                  .forEach(this::processStripe);
            chronometer.stop();
            log.warn("Duration: {} ms", String.format("%,.3f", chronometer.getDuration()));
            return matrix;
        }

        private void processStripe(final int stripe) {
            // Within selected column, process parallel multiplication per row.
            IntStream.range(0, height)
                  .parallel()
                  .forEach(row -> processStripe(row, stripe));
        }

        private void processStripe(final int row, final int stripe) {
            // For selected row and column in matrix A, compute multiplication against entire row in matrix B.
            IntStream.range(0, width)
                  .parallel()
                  .forEach(column -> multiply(row, stripe, column));
        }

        private void multiply(final int row, final int stripe, final int column) {

            final int valueA = matrixA.get(row, stripe);
            final int valueB = matrixB.get(stripe, column);
            final int product = valueA * valueB;

            values[row][column] += product;
        }

    }

}
