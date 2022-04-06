package org.dcu.student.sem2.ca670.algorithms;

import lombok.Data;
import lombok.Getter;
import lombok.extern.slf4j.Slf4j;
import org.dcu.student.sem2.ca670.matrices.Matrix;
import org.dcu.student.sem2.ca670.utils.Chronometer;

import javax.swing.*;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;
import java.util.stream.IntStream;

@Slf4j
public class ParallelReduceMatrixMultiplication implements MatrixMultiplication {

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
        private final Lock[][] locks;
        private final int[][] values;
        private final Matrix result;
        private final Chronometer chronometer = new Chronometer();
        private ExecutorService service = Executors.newWorkStealingPool();

        public Context(final Matrix matrixA, final Matrix matrixB) {

            log.info("Creating new context...");

            this.matrixA = matrixA;
            this.matrixB = matrixB;

            this.height = matrixA.getHeight();
            this.width = matrixB.getWidth();
            this.dimension = matrixA.getWidth();

            this.locks = new ReentrantLock[height][width];
            IntStream.range(0, height)
                  .forEach(i -> IntStream.range(0, width)
                        .forEach(j -> locks[i][j] = new ReentrantLock()));

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

            generateAndExecuteTasks();
            awaitCompletion();

            chronometer.stop();
            log.warn("Duration: {} ms", String.format("%,.3f", chronometer.getDuration()));

            return result;
        }

        private void generateAndExecuteTasks() {
            log.info("Generating and executing parallel tasks...");

            for (int row = 0; row < height; row++) {
                for (int column = 0; column < width; column++) {
                    values[row][column] = 0;
                    for (int stripe = 0; stripe < dimension; stripe++) {
                        final Task task = new Task(this, row, column, stripe);
                        service.execute(task);
                    }
                }
            }
            log.info("All tasks generated and completed.");
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
    private static class Task implements Runnable {

        private final Context context;

        private final int row;
        private final int column;
        private int stripe;

        public Task(final Context context, final int row, final int column, final int stripe) {
            this.context = context;

            this.row = row;
            this.column = column;
            this.stripe = stripe;
        }

        @Override
        public void run() {

            Thread.currentThread().setPriority(Thread.MAX_PRIORITY);

            final int valueA = context.matrixA.get(row, stripe);
            final int valueB = context.matrixB.get(stripe, column);
            final int product = valueA * valueB;

            final Lock lock = context.locks[row][column];
            while (!lock.tryLock()) {
                Thread.onSpinWait();
            }

            context.values[row][column] += product;
            lock.unlock();
        }

    }

}
