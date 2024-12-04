import java.io.*;
import java.nio.file.*;
import java.util.*;

public class day04_part1 {

    public static final String WORD_TO_FIND = "XMAS";
    public static final int WORD_LENGTH = WORD_TO_FIND.length();

    public static int countWordOccurrences(char[][] grid) {
        int count = 0;
        int rows = grid.length;
        int cols = grid[0].length;

        for (int y = 0; y < rows; y++)
            for (int x = 0; x < cols; x++) {
                if (matches(grid, y, x, 0, 1)) count++;
                if (matches(grid, y, x + WORD_LENGTH - 1, 0, -1)) count++;
                if (matches(grid, y, x, 1, 0)) count++;
                if (matches(grid, y + WORD_LENGTH - 1, x, -1, 0)) count++;
                if (matches(grid, y, x, 1, 1)) count++;
                if (matches(grid, y + WORD_LENGTH - 1, x, -1, 1)) count++;
                if (matches(grid, y, x + WORD_LENGTH - 1, 1, -1)) count++;
                if (matches(grid, y + WORD_LENGTH - 1, x + WORD_LENGTH - 1, -1, -1)) count++;
            }
        return count;
    }

    private static boolean matches(char[][] grid, int startRow, int startCol,
				   int rowIncrement, int colIncrement) {
        int row = startRow;
        int col = startCol;

        for (int x = 0; x < WORD_LENGTH; x++) {
            if (row < 0 || col < 0 || row >= grid.length
		|| col >= grid[0].length || grid[row][col] != WORD_TO_FIND.charAt(x))
                return false;
            row += rowIncrement;
            col += colIncrement;
        }
        return true;
    }

    public static char[][] stringToGrid(List<String> input) {
        int rows = input.size();
        int cols = input.get(0).length();
        char[][] grid = new char[rows][cols];

        for (int y = 0; y < rows; y++)
            grid[y] = input.get(y).toCharArray();
        return grid;
    }

    public static void main(String[] args) {
        if (args.length < 1) {
            System.out.println("Usage: java day04_part1 <inputFile>");
            return ;
        }
        String inputFile = args[0];
        List<String> lines = new ArrayList<>();
        try {
            lines = Files.readAllLines(Paths.get(inputFile));
        } catch (IOException e) {
            System.out.println("Error can't read fuile : " + e.getMessage());
            return ;
        }
        char[][] grid = stringToGrid(lines);
        int occurrences = countWordOccurrences(grid);
        System.out.println(occurrences);
    }
}
