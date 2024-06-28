package list08;

import javax.swing.*;
import java.awt.*;

public class CalendarApp {
    public static void main(String[] args) {
        EventQueue.invokeLater(() -> {
            MainApplicationFrame mainFrame = new MainApplicationFrame("CalendarApp");
            mainFrame.pack();
            mainFrame.setSize(new Dimension(1200, 800));
            mainFrame.setLocationRelativeTo(null);
            mainFrame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
            mainFrame.setVisible(true);
        });
    }
}