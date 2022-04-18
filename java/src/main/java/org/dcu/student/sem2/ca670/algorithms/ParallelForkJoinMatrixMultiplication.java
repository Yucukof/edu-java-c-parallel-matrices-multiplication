package org.dcu.student.sem2.ca670.algorithms;

import lombok.AllArgsConstructor;
import lombok.Builder;
import lombok.Data;
import lombok.EqualsAndHashCode;
import lombok.extern.slf4j.Slf4j;
import org.dcu.student.sem2.ca670.matrices.Matrix;
import org.dcu.student.sem2.ca670.utils.Chronometer;

import java.util.concurrent.ForkJoinPool;
import java.util.concurrent.RecursiveAction;
import java.util.concurrent.RecursiveTask;

/**
 * @author Hadrien BAILLY
 */
@Slf4j
public class ParallelForkJoinMatrixMultiplication implements MatrixMultiplication {

    @Override
    public Matrix apply(final Matrix matrixA, final Matrix matrixB) {

        log.info("Using {} method...", Algorithm.FORK_JOIN.getName());
        final Context context = new Context(matrixA, matrixB);
        return context.execute();
    }

    @Data
    @AllArgsConstructor
    @Builder(toBuilder = true)
    private static class Context {

        private final Matrix matrixA;
        private final Matrix matrixB;

        private final int height;
        private final int width;
        private final int dimension;

        private final int[][] values;

        private final Matrix result;

        private final Chronometer chronometer = new Chronometer();

        private ForkJoinPool pool = new ForkJoinPool();


        public Context(final Matrix matrixA, final Matrix matrixB) {

            log.info("Creating new context...");

            this.matrixA = matrixA;
            this.matrixB = matrixB;

            this.height = matrixA.getHeight();
            this.width = matrixB.getWidth();
            this.dimension = matrixA.getWidth();

            final String name = matrixA.getName() + "x" + matrixB.getName();
            final Matrix product = new Matrix(name);
            product.allocate(new int[height][width]);
            this.result = product;
            this.values = result.getValues();
        }


        public Matrix execute() {
            log.info("Executing multiplication...");

            Thread.currentThread().setPriority(Thread.MIN_PRIORITY);

            chronometer.start();

            final ForkTask mainTask = new ForkTask(this);
            pool.invoke(mainTask);

            chronometer.stop();
            log.warn("Duration: {} ms", String.format("%,.3f", chronometer.getDuration()));

            return result;
        }

    }

    @Data
    @AllArgsConstructor
    @Builder(toBuilder = true)
    @EqualsAndHashCode(callSuper = true)
    private static class ForkTask extends RecursiveAction {

        private final Context context;

        private final boolean root;

        private final int row;
        private final int column;
        private final int dimension;

        public ForkTask(final Context context) {

            this.context = context;
            this.root = true;
            this.row = context.height - 1;
            this.column = context.width - 1;
            this.dimension = context.dimension - 1;
        }

        @Override
        protected void compute() {

            if (column == context.width - 1 && row > 0) {
                this.toBuilder()
                      .row(row - 1)
                      .root(false)
                      .build()
                      .fork()
                      .join();
            }

            if (column > 0) {
                this.toBuilder()
                      .column(column - 1)
                      .build()
                      .fork()
                      .join();
            }

            computeDirectly();
        }

        private void computeDirectly() {

            for (int stripe = 0; stripe < context.dimension; stripe++) {

                final int valueA = context.matrixA.get(row, stripe);
                final int valueB = context.matrixB.get(stripe, column);
                final int product = valueA * valueB;

                context.values[row][column] += product;
            }
        }

    }

}
