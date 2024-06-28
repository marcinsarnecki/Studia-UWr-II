package org.example;

import lombok.Getter;
import lombok.Setter;

import javax.swing.*;
import java.awt.*;
import java.awt.event.MouseEvent;
import java.io.*;

public class PegSolitaireBoard extends JPanel {
    private static final int EMPTY = 0;
    private static final int PEG = 1;
    private static final int INVALID = -1;
    @Getter
    private Color backgroundColor = Color.WHITE;
    @Getter
    private Color pegColor = Color.BLACK;
    @Getter
    private Color activeColor = Color.GREEN;
    @Getter
    private Color holeColor = Color.GRAY;
    public void setBackgroundColor(Color color) {
        this.backgroundColor = color;
        repaint();
    }

    public void setPegColor(Color color) {
        this.pegColor = color;
        repaint();
    }

    public void setActiveColor(Color color) {
        this.activeColor = color;
        repaint();
    }
    public void setHoleColor(Color holeColor) {
        this.holeColor = holeColor;
        repaint();
    }

    public void setGameLoaded(boolean gameLoaded) {
        isGameLoaded = gameLoaded;
    }

    private boolean isGameLoaded;


    @Setter
    private boolean isBritish = true;

    @Setter
    @Getter
    private boolean isActive;

    @Setter
    private int[][] boardState = new int[7][7];

    @Setter
    private boolean[][] isValid = new boolean[7][7];
    private int selectedY = -1, selectedX = -1;

    public PegSolitaireBoard() {
        isActive = false;
    }

    public void processMouseClick(MouseEvent e) {
        if(!isActive)
            return;
        int mouseY = e.getY();
        int mouseX = e.getX();
        int startX = 95, startY = 60;
        int y = (mouseY - startY) / (holeRadius + holeMargin);
        int x = (mouseX - startX) / (holeRadius + holeMargin);
        if (isValidPosition(y, x)) {
            if (selectedY == -1 && selectedX == -1) {
                selectedY = y;
                selectedX = x;
            } else {
                if (isValidMove(selectedY, selectedX, y, x)) {
                    makeMove(selectedY, selectedX, y, x);
                    selectedY = -1;
                    selectedX = -1;
                } else {
                    selectedY = y;
                    selectedX = x;
                }
            }
        }
        else {
            selectedY = -1;
            selectedX = -1;
        }
        repaint();
    }
    private boolean isValidPosition(int y, int x) {
        if(y > 6 || y < 0 || x > 6 || x < 0)
            return false;
        return isValid[y][x];
    }

    private boolean isValidMove(int currentY, int currentX, int y, int x) {
        if(boardState[currentY][currentX] != PEG || boardState[y][x] != EMPTY)
            return false;
        return boardState[(currentY + y) / 2][(currentX + x) / 2] == PEG;
    }

    private void makeMove(int currentY, int currentX, int y, int x) {
        boardState[currentY][currentX] = EMPTY;
        boardState[(currentY + y) / 2][(currentX + x) / 2] = EMPTY;
        boardState[y][x] = PEG;
    }

    private void initializeBoard() {
        for (int y = 0; y < 7; y++) {
            for (int x = 0; x < 7; x++) {
                isValid[y][x] = true;
                if ((y < 2 || y > 4) && (x < 2 || x > 4)) {
                    boardState[y][x] = INVALID;
                    isValid[y][x] = false;
                } else if (y == 3 && x == 3) {
                    boardState[y][x] = EMPTY;
                } else {
                    boardState[y][x] = PEG;
                }
            }
        }
        if(!isBritish) {
            boardState[1][1] = boardState[1][5] = boardState[5][1] = boardState[5][5] = PEG;
            isValid[1][1] = isValid[1][5] = isValid[5][1] = isValid[5][5] = true;
        }
    }

    private final int holeRadius = 20;
    private final int holeMargin = 10;

    @Override
    public void paintComponent(Graphics g) {
        super.paintComponent(g);
        g.setColor(backgroundColor);
        g.fillRect(0, 0, getWidth(), getHeight());
        if (!isGameLoaded) {
            drawInitialMessage(g);
        } else {
            drawBoard(g);
        }
    }
    private void drawInitialMessage(Graphics g) {
        String message = "Choose style and start new game";
        Font font = new Font("Arial", Font.BOLD, 20);
        g.setFont(font);

        FontMetrics metrics = g.getFontMetrics(font);
        int x = (getWidth() - metrics.stringWidth(message)) / 2;
        int y = ((getHeight() - metrics.getHeight()) / 2) + metrics.getAscent();

        g.setColor(Color.BLACK);
        g.drawString(message, x, y);
    }

    private void drawBoard(Graphics g) {
        int startX = (getWidth() - (7 * holeRadius + 6 * holeMargin)) / 2;
        int startY = (getHeight() - (7 * holeRadius + 6 * holeMargin)) / 2;
        Graphics2D g2d = (Graphics2D) g;
        g2d.setRenderingHint(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON);

        for (int col = 0; col < 7; col++) {
            for (int row = 0; row < 7; row++) {
                int x = startX + row * (holeRadius + holeMargin);
                int y = startY + col * (holeRadius + holeMargin);
                if (boardState[row][col] == INVALID)
                    continue;
                if (col == selectedY && row == selectedX) {
                    g2d.setColor(Color.GRAY);
                    g2d.fillOval(x + 2, y + 2, holeRadius, holeRadius);
                    GradientPaint gp = new GradientPaint(
                            x, y, activeColor.darker(),
                            x + holeRadius, y + holeRadius, activeColor.brighter(), true);
                    g2d.setPaint(gp);
                    g2d.fillOval(x, y, holeRadius, holeRadius);
                } else if (boardState[col][row] == PEG) {
                    g2d.setColor(Color.GRAY);
                    g2d.fillOval(x + 2, y + 2, holeRadius, holeRadius);
                    GradientPaint gp = new GradientPaint(
                            x, y, pegColor.darker(),
                            x + holeRadius, y + holeRadius, pegColor.brighter(), true);
                    g2d.setPaint(gp);
                    g2d.fillOval(x, y, holeRadius, holeRadius);
                }
                else {
                    g2d.setColor(holeColor);
                    g2d.fillOval(x, y, holeRadius, holeRadius);
                }
            }
        }
    }

    public void resetBoard() {
        initializeBoard();
        repaint();
    }

    public void saveBoardState() {
        if(!isGameLoaded)
            return;
        try (FileOutputStream fileOut = new FileOutputStream("solitaire.ser");
             ObjectOutputStream out = new ObjectOutputStream(fileOut)) {
            out.writeObject(new BoardState(boardState, isValid, isBritish));
        } catch (IOException e) {
            System.err.println("Error saving board state: " + e.getMessage());
        }
    }

    public BoardState loadBoardState() {
        try (FileInputStream fileIn = new FileInputStream("solitaire.ser");
             ObjectInputStream in = new ObjectInputStream(fileIn)) {
            return (BoardState) in.readObject();
        } catch (IOException | ClassNotFoundException e) {
            System.err.println("Error loading board state: " + e.getMessage());
            return null;
        }
    }

    public int checkGameState() {// 1 win // 0 loose // -1 still going
        int pegs = 0;
        int[] dy = {-2, 0, 2, 0}, dx = {0, 2, 0, -2};
        for (int y = 0; y < 7; y++) {
            for (int x = 0; x < 7; x++) {
                for(int dir = 0; dir < 4; dir++) {
                    int y2 = y + dy[dir], x2 = x + dx[dir];
                    if(isValidPosition(y, x) && boardState[y][x] == PEG)
                        pegs++;
                    if(isValidPosition(y, x) && isValidPosition(y2, x2) && isValidMove(y, x, y2, x2))
                        return -1;
                }
            }
        }
        if(pegs == 1 && boardState[3][3] == PEG)
            return 1;
        return 0;
    }
}