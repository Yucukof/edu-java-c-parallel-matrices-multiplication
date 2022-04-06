package org.dcu.student.sem2.ca670.algorithms;

import lombok.Builder;
import lombok.Data;
import lombok.Getter;
import lombok.RequiredArgsConstructor;
import lombok.extern.slf4j.Slf4j;
import org.dcu.student.sem2.ca670.matrices.Matrix;
import org.dcu.student.sem2.ca670.utils.Chronometer;

import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

@Slf4j
public class ParallelStripeMatrixMultiplication implements MatrixMultiplication {

    @Override
    public Matrix apply(final Matrix matrixA, final Matrix matrixB) {
        log.info("Using {} method...", Algorithm.REDUCE.getName());
        final Context context = new Context(matrixA, matrixB);
        return context.execute();
    }

    @Getter
    private static final class Context {

        private final ExecutorService service = Executors.newWorkStealingPool();

        private final Matrix matrixA;
        private final Matrix matrixB;

        private final int height;
        private final int width;
        private final int dimension;

        private final Matrix result;

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

            this.result = product;
        }

        public Matrix execute() {
            log.info("Executing multiplication...");

            chronometer.start();

            generateAndExecuteTasks();
            awaitCompletion();

            chronometer.stop();

            log.warn("Duration: {} ms", String.format("%,.3f", chronometer.getDuration()));

            return result;
        }

        private void generateAndExecuteTasks() {
            log.info("Generating and executing tasks...");
            for (int row = 0; row < height; row++) {
                for (int column = 0; column < width; column++) {
                    final Task task = new Task(this, row, column);
                    service.execute(task);
                }
            }
            log.info("Tasks generated.");
        }

        private void awaitCompletion() {
            log.info("Awaiting completion...");
            service.shutdown();
            while (!service.isTerminated()) {
                Thread.onSpinWait();
            }
            log.info("All tasks completed.");
        }

    }

    @Data
    @RequiredArgsConstructor
    @Builder(toBuilder = true)
    private static class Task implements Runnable {

        private final Context context;

        private final int row;
        private final int column;

        @Override
        public void run() {

            final Matrix matrixA = context.matrixA;
            final Matrix matrixB = context.matrixB;
            final Matrix result = context.result;

            final int[][] values = result.getValues();
            values[row][column] = 0;

            final int dimension = context.getDimension();
            for (int stripe = 0; stripe < dimension; stripe++) {

                final int valueA = matrixA.get(row, stripe);
                final int valueB = matrixB.get(stripe, column);

                final int product = valueA * valueB;

                values[row][column] += product;
            }
        }

    }

}
