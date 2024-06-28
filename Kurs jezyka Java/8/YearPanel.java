package list08;

import javax.swing.*;
import java.awt.*;
import java.util.GregorianCalendar;

public class YearPanel extends JPanel {
    private GregorianCalendar calendar;
    private MonthPanel[] months;

    public YearPanel(GregorianCalendar calendar) {
        this.calendar = (GregorianCalendar) calendar.clone();
        setLayout(new GridLayout(3, 4));
        populatePanel();
    }

    private void populatePanel() {
        months = new MonthPanel[12];
        setLayout(new GridLayout(3, 4, 10, 10)); 
        for (int i = 0; i < 12; i++) {
            GregorianCalendar monthCalendar = (GregorianCalendar) calendar.clone();
            monthCalendar.set(GregorianCalendar.MONTH, i);
            months[i] = new MonthPanel(monthCalendar);
            add(months[i]);
        }
    }

    public void updatePanel(GregorianCalendar newCalendar) {
        this.calendar = (GregorianCalendar) newCalendar.clone();
        removeAll();
        populatePanel();
        revalidate();
        repaint();
    }
}