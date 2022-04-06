package org.dcu.student.sem2.ca670.algorithms;

import lombok.extern.slf4j.Slf4j;
import org.dcu.student.sem2.ca670.matrices.Matrix;
import org.dcu.student.sem2.ca670.matrices.MatrixLoader;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.junit.runners.Parameterized;

import java.util.Arrays;
import java.util.List;

import static org.assertj.core.api.Assertions.assertThat;
import static org.dcu.student.sem2.ca670.algorithms.Algorithm.*;

@Slf4j
@RunWith(Parameterized.class)
public class MultiplicationTestByMatrix {

    private final Algorithm algorithm;

    public MultiplicationTestByMatrix(final Algorithm algorithm) {
        log.info("Performing Matrices Multiplication Test...");
        log.warn("Selected algorithm: {}", algorithm.getName());
        this.algorithm = algorithm;
    }

    @Parameterized.Parameters
    public static List<Object[]> primeNumbers() {
        return Arrays.asList(new Object[][]{
              {SEQUENTIAL},
              {STRIPE},
              {STREAM},
              {REDUCE}
        });
    }

    @Test
    public void given_gigantic_matrices_when_multiply_then_expect_correct_result() {

        if (algorithm == REDUCE) {
            log.warn("Skipping test");
            return;
        }

        final String name = "gigantic";

        log.info("Setting up...");
        final Matrix A = MatrixLoader.from(name.concat("A"));
        final Matrix B = MatrixLoader.from(name.concat("B"));

        log.info("Performing test...");
        final Matrix product = algorithm.multiply(A, B);
        assertThat(product).isNotNull();

        log.info("Validating result...");
        final Matrix C = MatrixLoader.from(name.concat("C"));
        assertThat(product.matches(C)).isTrue();
    }

    @Test
    public void given_humongous_matrices_when_multiply_then_expect_correct_result() {

        final String name = "humongous";

        log.info("Setting up...");
        final Matrix A = MatrixLoader.from(name.concat("A"));
        final Matrix B = MatrixLoader.from(name.concat("B"));

        log.info("Performing test...");
        final Matrix product = algorithm.multiply(A, B);
        assertThat(product).isNotNull();

        log.info("Validating result...");
        final Matrix C = MatrixLoader.from(name.concat("C"));
        assertThat(product.matches(C)).isTrue();
    }

    @Test
    public void given_large_matrices_when_multiply_then_expect_correct_result() {

        final String name = "large";

        log.info("Setting up...");
        final Matrix A = MatrixLoader.from(name.concat("A"));
        final Matrix B = MatrixLoader.from(name.concat("B"));

        log.info("Performing test...");
        final Matrix product = algorithm.multiply(A, B);
        assertThat(product).isNotNull();

        log.info("Validating result...");
        final Matrix C = MatrixLoader.from(name.concat("C"));
        assertThat(product.matches(C)).isTrue();
    }

    @Test
    public void given_medium_matrices_when_multiply_then_expect_correct_result() {

        final String name = "medium";

        log.info("Setting up...");
        final Matrix A = MatrixLoader.from(name.concat("A"));
        final Matrix B = MatrixLoader.from(name.concat("B"));

        log.info("Performing test...");
        final Matrix product = algorithm.multiply(A, B);
        assertThat(product).isNotNull();

        log.info("Validating result...");
        final Matrix C = MatrixLoader.from(name.concat("C"));
        assertThat(product.matches(C)).isTrue();
    }

    @Test
    public void given_nightmarish_matrices_when_multiply_then_expect_correct_result() {

        if (algorithm == REDUCE) {
            log.warn("Skipping test");
            return;
        }

        final String name = "nightmarish";

        log.info("Setting up...");
        final Matrix A = MatrixLoader.from(name.concat("A"));
        final Matrix B = MatrixLoader.from(name.concat("B"));

        log.info("Performing test...");
        final Matrix product = algorithm.multiply(A, B);
        assertThat(product).isNotNull();

        log.info("Validating result...");
        final Matrix C = MatrixLoader.from(name.concat("C"));
        assertThat(product.matches(C)).isTrue();
    }

    @Test
    public void given_rectangular_matrices_when_multiply_then_expect_correct_result() {

        final String name = "rectangular";

        log.info("Setting up...");
        final Matrix A = MatrixLoader.from(name.concat("A"));
        final Matrix B = MatrixLoader.from(name.concat("B"));

        log.info("Performing test...");
        final Matrix product = algorithm.multiply(A, B);
        assertThat(product).isNotNull();

        log.info("Validating result...");
        final Matrix C = MatrixLoader.from(name.concat("C"));
        assertThat(product.matches(C)).isTrue();
    }

    @Test
    public void given_simple_matrices_when_multiply_then_expect_correct_result() {

        final String name = "simple";

        log.info("Setting up...");
        final Matrix A = MatrixLoader.from(name.concat("A"));
        final Matrix B = MatrixLoader.from(name.concat("B"));

        log.info("Performing test...");
        final Matrix product = algorithm.multiply(A, B);
        assertThat(product).isNotNull();

        log.info("Validating result...");
        final Matrix C = MatrixLoader.from(name.concat("C"));
        assertThat(product.matches(C)).isTrue();
    }

}