package list08;

import javax.swing.*;
import java.awt.*;
import java.util.Calendar;
import java.util.GregorianCalendar;

public class ControlPanel extends JToolBar {
    private JScrollBar monthScrollBar;
    private JSpinner yearSpinner;

    public ControlPanel(GregorianCalendar calendar) {
        // Adjust the FlowLayout to include horizontal and vertical gaps
        setLayout(new FlowLayout(FlowLayout.LEADING, 10, 5)); // 10 pixels horizontal gap, 5 pixels vertical gap
        setFloatable(false);

        createYearSpinner(calendar);
        add(yearSpinner);

        // Spacer between yearSpinner and monthScrollBar
        add(Box.createRigidArea(new Dimension(10, 0)));

        createMonthScrollBar(calendar);
        add(monthScrollBar);
    }

    private void createMonthScrollBar(GregorianCalendar calendar) {
        monthScrollBar = new JScrollBar(JScrollBar.HORIZONTAL, calendar.get(Calendar.MONTH), 1, 0, 12);
        monthScrollBar.addAdjustmentListener(e -> firePropertyChange("monthChange", -1, monthScrollBar.getValue()));

        // Adjust the size of the scrollbar if needed
        monthScrollBar.setPreferredSize(new Dimension(400, 20));
        monthScrollBar.setMaximumSize(new Dimension(400, 20));
        monthScrollBar.setMinimumSize(new Dimension(150, 20));
    }

    private void createYearSpinner(GregorianCalendar calendar) {
        SpinnerModel yearModel = new SpinnerNumberModel(calendar.get(Calendar.YEAR), 1, null, 1);
        yearSpinner = new JSpinner(yearModel);
        yearSpinner.addChangeListener(e -> firePropertyChange("yearChange", 0, yearSpinner.getValue()));

        // Adjust the size of the spinner if needed
        yearSpinner.setPreferredSize(new Dimension(80, 20));
        yearSpinner.setMaximumSize(new Dimension(80, 20));
        yearSpinner.setMinimumSize(new Dimension(80, 20));
    }
}