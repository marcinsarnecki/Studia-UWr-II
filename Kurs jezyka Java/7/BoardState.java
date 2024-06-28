package org.example;
import java.io.Serial;
import java.io.Serializable;

public record BoardState(int[][] state, boolean[][] isValid,
                          boolean isBritish) implements Serializable {
    @Serial
    private static final long serialVersionUID = 1L;
}
