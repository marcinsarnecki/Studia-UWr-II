package list08;

import javax.swing.*;
import java.awt.*;
import java.time.LocalDate;

public class DayPanel extends JPanel {
    private final JLabel dayLabel;
    private boolean isSunday;
    private boolean isToday;

    public DayPanel(int day, boolean isSunday, boolean isToday) {
        this.isSunday = isSunday;
        this.isToday = isToday;
        setLayout(new BorderLayout());
        dayLabel = new JLabel(day > 0 ? Integer.toString(day) : "", SwingConstants.CENTER);
        add(dayLabel, BorderLayout.CENTER);
        applyStyles();
    }

    private void applyStyles() {
        if (isToday) {
            setBackground(Color.YELLOW);
        } else if (isSunday) {
            setBackground(Color.PINK);
        } else {
            setBackground(Color.WHITE);
        }
        setBorder(BorderFactory.createLineBorder(Color.BLACK, 1)); // Thinner border
    }
    public void setDay(int day, boolean isSunday, boolean isToday) {
        this.isSunday = isSunday;
        this.isToday = isToday;
        dayLabel.setText(day > 0 ? Integer.toString(day) : "");
        applyStyles();
    }
}