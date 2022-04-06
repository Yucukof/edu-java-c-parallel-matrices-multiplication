package org.dcu.student.sem2.ca670.matrices;

import lombok.AccessLevel;
import lombok.Data;
import lombok.Setter;
import lombok.extern.slf4j.Slf4j;

import java.util.Arrays;
import java.util.List;
import java.util.Objects;

/**
 * A class representing a bi-dimensional matrix composed of integers.
 *
 * @author Hadrien BAILLY.
 */
@Slf4j
@Data
public class Matrix {

    /**
     * The name of the matrix
     */
    private String name;

    /**
     * The inner, raw representation of the matrix.
     */
    private int[][] values;

    /**
     * The number of rows in the matrix.
     */
    @Setter(AccessLevel.PRIVATE)
    private int height;
    /**
     * The number of columns in the matrix.
     */
    @Setter(AccessLevel.PRIVATE)
    private int width;

    /**
     * A constructor with some logging.
     * @param name the name of the matrix to create.
     */
    public Matrix(final String name) {
        log.info("Creating empty matrix...");
        this.name = name;
    }

    /**
     * Allocate the given memory space to the current matrix.
     * @param values the memory space to allocate.
     */
    public void allocate(final int[][] values) {
        log.info("Allocating memory for [{},{}] matrix...", values.length, values[0].length);
        if (!isValidInput(values)) {
            throw new IllegalArgumentException("Invalid matrix input");
        }
        this.values = values;
        this.height = values.length;
        this.width = values[0].length;

        log.info("Memory allocated.");
    }

    /**
     * Checks if the given input is valid for representing a matrix.
     * @param values the inner representation of a matrix.
     * @return true if the values are a valid bi-dimensional matrix, false otherwise.
     */
    private boolean isValidInput(final int[][] values) {
        return values != null && values.length > 0
              && Arrays.stream(values).noneMatch(Objects::isNull)
              && values[0].length > 0;
    }

    /**
     * Fills the memory space of the matrix with the given values.
     * @param rows the values to use for filling the memory.
     */
    public void fill(final List<String[]> rows) {
        log.info("Filling [{},{}] matrix...", height, width);
        log.info("Copying matrix's file content...");
        for (int row = 0; row < height; row++) {
            final String[] cells = rows.get(row);
            for (int colum = 0; colum < width; colum++) {
                values[row][colum] = Integer.parseUnsignedInt(cells[colum]);
            }
        }
        log.info("Matrix's file content copied.");
    }

    /**
     *
     * @return true if the matrix's dimensions are [x,1], false otherwise.
     */
    public boolean isColumn() {
        return getWidth() == 1 && getHeight() > 1;
    }

    /**
     *
     * @return true if the matrix's dimensions are [x,y] (where x != y), false otherwise.
     */
    public boolean isRectangular() {
        return getWidth() != getHeight();
    }

    /**
     *
     * @return true if the matrix's dimensions are [1,y], false otherwise.
     */
    public boolean isRow() {
        return getWidth() > 1 && getHeight() == 1;
    }

    /**
     *
     * @return true if the matrix's dimensions are [1,1], false otherwise.
     */
    public boolean isSingleton() {
        return getWidth() == 1 && getHeight() == 1;
    }

    /**
     *
     * @return true if the matrix's dimensions are [x,x] (where x > 1), false otherwise.
     */
    public boolean isSquare() {
        return getWidth() == getHeight();
    }

    /**
     * Check if the current matrix is equivalent to the given matrix.
     * @param that the given matrix to which compare against equivalence.
     * @return true if the two matrices have the same dimensions and contents, false otherwise.
     */
    public boolean matches(Matrix that) {
        log.info("Comparing matrix [{}] with matrix [{}]", this.getName(), that.getName());
        if (this.height != that.height || this.width != that.width) {
            throw new IllegalArgumentException(String.format("Cannot compare [%s,%s] matrix %s with [%s,%s] matrix %s"
                  , this.height, this.width, this.name, that.height, that.width, that.name));
        }
        for (int row = 0; row < this.height; row++) {
            for (int column = 0; column < this.width; column++) {
                if (this.values[row][column] != that.values[row][column]) {
                    log.info("Matrices do not match.");
                    return false;
                }
            }
        }
        log.info("Matrices match.");
        return true;
    }

    /**
     * Display the current matrix on screen.
     * <br>
     * CAUTION: on large matrices, may cause the machine to become unresponsive.
     */
    public void print() {
        log.info("Displaying matrix [{}]", name);
        for (int row = 0; row < height; row++) {
            for (int column = 0; column < width; column++) {
                if (column > 0) {
                    System.out.print(" ");
                }
                final int value = get(row, column);
                System.out.print(String.format("%3d", value));
            }
            System.out.println();
        }
    }

    /**
     * Return the value at the given coordinates in the current matrix.
     * @param row the row ordinate x.
     * @param column the column ordinate y.
     * @return the value contained at [x,y].
     * @throws IllegalArgumentException when the coordinates are invalid (not contained in the matrix).
     * @see #contains(int, int)
     */
    public int get(final int row, final int column) {
        if (!contains(row, column))
            throw new IllegalArgumentException(String.format("Invalid coordinate: [%s,%s] (dimensions: [%s,%s])", row, column, getHeight(), getWidth()));
        return values[row][column];
    }

    /**
     * Check if the given coordinates are contained in the current matrix.
     * @param row the row ordinate x.
     * @param column the column ordinate y.
     * @return true if the coordinates [x,y] are contained in the table, false otherwise.
     */
    public boolean contains(final int row, final int column) {
        return column >= 0 && column < getWidth()
              && row >= 0 && row < getHeight();
    }

}
