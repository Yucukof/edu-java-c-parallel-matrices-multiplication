package org.dcu.student.sem2.ca670.algorithms;

import lombok.extern.slf4j.Slf4j;
import org.dcu.student.sem2.ca670.matrices.Matrix;
import org.dcu.student.sem2.ca670.matrices.MatrixLoader;
import org.junit.Ignore;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.junit.runners.Parameterized;

import java.util.Arrays;
import java.util.List;

import static org.assertj.core.api.Assertions.assertThat;
import static org.dcu.student.sem2.ca670.algorithms.Algorithm.*;

@Slf4j
@RunWith(Parameterized.class)
public class MultiplicationTestByAlgorithm {

    private final String name;
    private final boolean detailed;

    public MultiplicationTestByAlgorithm(final String name, final boolean detailed) {
        log.info("Performing Matrices Multiplication Test...");
        log.warn("Selected matrices group: {}", name);
        this.name = name;
        this.detailed = detailed;
    }

    @Parameterized.Parameters
    public static List<Object[]> primeNumbers() {
        return Arrays.asList(new Object[][]{
              {"simple", true},
              {"medium", true},
              {"large", false},
              {"humongous", false},
              {"nightmarish", false}
        });
    }

    @Test
    @Ignore("This algorithm is under-achieving, and will cause Java heap exhaustion on large dense matrices because of the overhead incurred by the Runnable generation.")
    public void given_the_REDUCE_algorithm_when_multiply_then_expect_correct_result() {

        log.info("Setting up...");
        final Matrix A = MatrixLoader.from(name.concat("A"));
        if (detailed) A.print();

        final Matrix B = MatrixLoader.from(name.concat("B"));
        if (detailed) B.print();

        final Matrix product = REDUCE.multiply(A, B);

        assertThat(product).isNotNull();
        if (detailed) product.print();

        final Matrix C = MatrixLoader.from(name.concat("C"));
        if (detailed) C.print();

        assertThat(product.matches(C)).isTrue();
    }

    @Test
    public void given_the_SEQUENTIAL_algorithm_when_multiply_then_expect_correct_result() {

        log.info("Setting up...");
        final Matrix A = MatrixLoader.from(name.concat("A"));
        log.info("Matrix A");
        if (detailed) A.print();

        final Matrix B = MatrixLoader.from(name.concat("B"));
        log.info("Matrix B");
        if (detailed) B.print();

        final Matrix product = SEQUENTIAL.multiply(A, B);

        assertThat(product).isNotNull();
        if (detailed) product.print();

        final Matrix C = MatrixLoader.from(name.concat("C"));
        log.info("Expected Matrix");
        if (detailed) C.print();

        assertThat(product.matches(C)).isTrue();
    }

    @Test
    public void given_the_STREAM_when_multiply_then_expect_correct_result() {

        log.info("Setting up...");
        final Matrix A = MatrixLoader.from(name.concat("A"));
        log.info("Matrix A");
        if (detailed) A.print();

        final Matrix B = MatrixLoader.from(name.concat("B"));
        log.info("Matrix B");
        if (detailed) B.print();

        final Matrix product = STREAM.multiply(A, B);

        assertThat(product).isNotNull();
        if (detailed) product.print();

        final Matrix C = MatrixLoader.from(name.concat("C"));
        log.info("Expected Matrix");
        if (detailed) C.print();

        assertThat(product.matches(C)).isTrue();
    }

    @Test
    public void given_the_STRIPE_algorithm_when_multiply_then_expect_correct_result() {

        log.info("Setting up...");
        final Matrix A = MatrixLoader.from(name.concat("A"));
        log.info("Matrix A");
        if (detailed) A.print();

        final Matrix B = MatrixLoader.from(name.concat("B"));
        log.info("Matrix B");
        if (detailed) B.print();

        final Matrix product = STRIPE.multiply(A, B);

        assertThat(product).isNotNull();
        if (detailed) product.print();

        final Matrix C = MatrixLoader.from(name.concat("C"));
        log.info("Expected Matrix");
        if (detailed) C.print();

        assertThat(product.matches(C)).isTrue();
    }

}