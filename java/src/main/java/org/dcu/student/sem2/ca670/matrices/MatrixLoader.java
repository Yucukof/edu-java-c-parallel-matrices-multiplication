package org.dcu.student.sem2.ca670.matrices;

import lombok.AccessLevel;
import lombok.NoArgsConstructor;
import lombok.extern.slf4j.Slf4j;

import java.io.*;
import java.util.ArrayList;
import java.util.List;

/**
 * A matrix utility class used to load given matrices from a directory into memory.
 *
 * @author Hadrien BAILLY.
 */
@Slf4j
@NoArgsConstructor(access = AccessLevel.PRIVATE)
public class MatrixLoader {

    /**
     * The name of the directory containing the matrices, and of the matrix file extension.
     */
    private static final String MTX = "mtx";

    /**
     * Load a matrix from the matrix directory.
     * @param name the name of the matrix to laod.
     * @return a bi-dimensional matrix.
     * @throws IllegalArgumentException if the matrix file cannot be found.
     * @throws RuntimeException if any IO exception occurs.
     */
    public static Matrix from(final String name) {
        final String filename = name + "." + MTX;
        final File file = new File(MTX, filename);
        return from(name, file);
    }

    /**
     * Load a matrix from the given file.
     * @param name the name to give to the matrix.
     * @param file the file containing the data to inject.
     * @return a bi-dimensional matrix.
     * @throws IllegalArgumentException if the matrix file cannot be found.
     * @throws RuntimeException if any IO exception occurs.
     */
    public static Matrix from(final String name, final File file) {

        log.info("Loading new matrix [{}]...", name);
        Matrix matrix = new Matrix(name);

        final List<String[]> rows = loadRows(file);
        final int[][] values = estimate(rows);

        matrix.allocate(values);
        matrix.fill(rows);

        return matrix;

    }

    /**
     * Load the bi-dimensional data from the given matrix file.
     * @param file the file from which load the rows.
     * @return a list of matrix values organised in rows and columns.
     * @throws IllegalArgumentException if the matrix file cannot be found.
     * @throws RuntimeException if any IO exception occurs.
     */
    private static List<String[]> loadRows(final File file) {
        log.info("Loading rows from file [{}]...", file.getName());

        try (BufferedReader br = new BufferedReader((new FileReader(file)))) {

            final List<String[]> rows = new ArrayList<>();
            for (String line; (line = br.readLine()) != null; ) {
                final String[] row = line.split("[ \t]");
                rows.add(row);
            }

            log.info("Rows loaded.");
            return rows;

        } catch (FileNotFoundException e) {
            throw new IllegalArgumentException(String.format("File [%s] does not exist!", file.getName()), e);
        } catch (IOException e) {
            throw new RuntimeException(String.format("Error occurred when reading file [%s]!", file.getName()), e);
        }
    }

    /**
     * Estimates the memory need for the given matrix data.
     * @param rows the matrix data loaded from a file.
     * @return a bi-dimensional memory space.
     */
    private static int[][] estimate(final List<String[]> rows) {
        log.info("Estimating memory need...");
        final int height = rows.size();
        final int width = rows.stream()
              .map(array -> array.length)
              .reduce(Math::max)
              .orElse(0);
        log.info("Memory needs: [{},{}]", height, width);
        return new int[height][width];
    }

}
