package org.example;

import javax.swing.*;
import java.awt.*;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;

public class PegSolitaire extends JFrame {
    private final PegSolitaireBoard gameBoard;
    private final JLabel statusLabel;
    private JRadioButtonMenuItem britishStyle;
    private JRadioButtonMenuItem europeanStyle;

    public PegSolitaire() {
        setTitle("Peg Solitaire");
        setSize(400, 400);
        setResizable(false);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLayout(new BorderLayout());

        createMenuBar();

        gameBoard = new PegSolitaireBoard();
        BoardState loadedState = gameBoard.loadBoardState();
        if (loadedState != null) {
            gameBoard.setBoardState(loadedState.state());
            gameBoard.setIsValid(loadedState.isValid());
            gameBoard.setBritish(loadedState.isBritish());
            updateBoardActivity(true);
            gameBoard.setGameLoaded(true);
        } else {
            gameBoard.setGameLoaded(false);
        }

        add(gameBoard, BorderLayout.CENTER);
        statusLabel = new JLabel("Welcome to Peg Solitaire!");
        add(statusLabel, BorderLayout.SOUTH);

        setVisible(true);
        gameBoard.addMouseListener(new MouseAdapter() {
            @Override
            public void mouseClicked(MouseEvent e) {
                gameBoard.processMouseClick(e);
                checkIfGameEnded();
            }
        });
        checkIfGameEnded();
    }

    void checkIfGameEnded() {
        int state = gameBoard.checkGameState();
        if(state == 0) {
            statusLabel.setText("You lost");
            updateBoardActivity(false);
        }
        if(state == 1) {
            statusLabel.setText("You won");
            updateBoardActivity(false);
        }
    }

    private void createMenuBar() {
        JMenuBar menuBar = new JMenuBar();

        JMenu gameMenu = new JMenu("Game");
        JMenuItem newGame = new JMenuItem("New Game");
        JMenuItem endGame = new JMenuItem("End Game");
        gameMenu.add(newGame);
        gameMenu.add(endGame);

        newGame.addActionListener(e -> startNewGame());
        endGame.addActionListener(e -> endCurrentGame());

        JMenu settingsMenu = new JMenu("Settings");
        britishStyle = new JRadioButtonMenuItem("British (33 holes)");
        europeanStyle = new JRadioButtonMenuItem("European (37 holes)");

        ButtonGroup group = new ButtonGroup();
        group.add(britishStyle);
        group.add(europeanStyle);

        britishStyle.addActionListener(e -> setBoardStyle("British"));
        europeanStyle.addActionListener(e -> setBoardStyle("European"));

        settingsMenu.add(britishStyle);
        settingsMenu.add(europeanStyle);

        JMenuItem backgroundColorItem = new JMenuItem("Background Color");
        JMenuItem pegColorItem = new JMenuItem("Peg Color");
        JMenuItem activeColorItem = new JMenuItem("Active Peg Color");
        JMenuItem holeColorItem = new JMenuItem("Hole Color");

        holeColorItem.addActionListener(e -> chooseHoleColor());
        backgroundColorItem.addActionListener(e -> chooseBackgroundColor());
        pegColorItem.addActionListener(e -> choosePegColor());
        activeColorItem.addActionListener(e -> chooseActiveColor());

        settingsMenu.add(activeColorItem);
        settingsMenu.add(holeColorItem);
        settingsMenu.add(backgroundColorItem);
        settingsMenu.add(pegColorItem);

        JMenu helpMenu = new JMenu("Help");
        JMenuItem aboutGame = new JMenuItem("About Game");
        JMenuItem aboutApp = new JMenuItem("About App");

        aboutGame.addActionListener(e -> showAboutGame());
        aboutApp.addActionListener(e -> showAboutApp());

        helpMenu.add(aboutGame);
        helpMenu.add(aboutApp);

        menuBar.add(gameMenu);
        menuBar.add(settingsMenu);
        menuBar.add(Box.createHorizontalGlue());
        menuBar.add(helpMenu);

        setJMenuBar(menuBar);
    }

    private void setBoardStyle(String style) {
        if(gameBoard.isActive())
            return;
        if ("British".equals(style)) {
            gameBoard.setBritish(true);
        } else if ("European".equals(style)) {
            gameBoard.setBritish(false);
        }
    }

    private void showAboutGame() {
        JOptionPane.showMessageDialog(this,
                "Peg Solitaire is a board game for one player involving movement of pegs on a board with holes.",
                "About Game",
                JOptionPane.INFORMATION_MESSAGE);
    }

    private void showAboutApp() {
        JOptionPane.showMessageDialog(this,
                "Author: Marcin Sarnecki\nDate: 2023\nThis is a simple Peg Solitaire game application.",
                "About App",
                JOptionPane.INFORMATION_MESSAGE);
    }

    private void startNewGame() {
        gameBoard.resetBoard();
        gameBoard.setGameLoaded(true);
        updateBoardActivity(true);
        statusLabel.setText("New Game Started");
    }

    private void endCurrentGame() {
        gameBoard.saveBoardState();
        System.exit(0);
    }

    private void updateRadioButtonsBasedOnBoardState() {
        britishStyle.setEnabled(!gameBoard.isActive());
        europeanStyle.setEnabled(!gameBoard.isActive());
    }

    public void updateBoardActivity(boolean isActive) {
        gameBoard.setActive(isActive);
        updateRadioButtonsBasedOnBoardState();
    }
    private void chooseBackgroundColor() {
        Color newColor = JColorChooser.showDialog(this, "Choose Background Color", gameBoard.getBackgroundColor());
        if (newColor != null) {
            gameBoard.setBackgroundColor(newColor);
            gameBoard.repaint();
        }
    }

    private void choosePegColor() {
        Color newColor = JColorChooser.showDialog(this, "Choose Peg Color", gameBoard.getPegColor());
        if (newColor != null) {
            gameBoard.setPegColor(newColor);
            gameBoard.repaint();
        }
    }

    private void chooseHoleColor() {
        Color newColor = JColorChooser.showDialog(this, "Choose Hole Color", gameBoard.getHoleColor());
        if (newColor != null) {
            gameBoard.setHoleColor(newColor);
            gameBoard.repaint();
        }
    }

    private void chooseActiveColor() {
        Color newColor = JColorChooser.showDialog(this, "Choose Active Peg Color", gameBoard.getActiveColor());
        if (newColor != null) {
            gameBoard.setActiveColor(newColor);
            gameBoard.repaint();
        }
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(PegSolitaire::new);
    }
}