package org.dcu.student.sem2.ca670.algorithms;

import lombok.extern.slf4j.Slf4j;
import org.dcu.student.sem2.ca670.matrices.Matrix;
import org.dcu.student.sem2.ca670.utils.Chronometer;

@Slf4j
public class SequentialMatrixMultiplication implements MatrixMultiplication {

    @Override
    public Matrix apply(final Matrix a, final Matrix b) {

        log.info("Using {} method...", Algorithm.SEQUENTIAL.getName());

        final String name = a.getName() + "x" + b.getName();
        final Matrix product = new Matrix(name);

        final int heightA = a.getHeight();
        final int widthB = b.getWidth();

        product.allocate(new int[heightA][widthB]);

        execute(a, b, product, heightA, widthB);

        return product;
    }

    private void execute(final Matrix a, final Matrix b, final Matrix product, final int heightA, final int widthB) {
        log.info("Executing multiplication...");

        final Chronometer chronometer = new Chronometer();
        chronometer.start();

        final int[][] values = product.getValues();
        for (int column = 0; column < widthB; column++) {
            for (int row = 0; row < heightA; row++) {
                values[row][column] = computeCell(a, b, row, column);
            }
        }
        chronometer.stop();

        log.warn("Duration: {} ms", String.format("%,.3f", chronometer.getDuration()));
    }

    private int computeCell(final Matrix a, final Matrix b, final int row, final int column) {

        final int heightB = b.getHeight();

        int sum = 0;
        for (int i = 0; i < heightB; i++) {
            final int valueA = a.get(row, i);
            final int valueB = b.get(i, column);
            sum += valueA * valueB;
        }
        return sum;
    }

}
