package list08;

import javax.swing.*;
import java.awt.*;
import java.text.SimpleDateFormat;
import java.util.Calendar;
import java.util.GregorianCalendar;
import java.util.Locale;

public class MainApplicationFrame extends JFrame { //todo refactor tak jak rzechon chce
    private JTabbedPane calendarTabbedPane;
    private YearPanel yearPanel;
    private MonthListPanel monthListPanel;
    private ControlPanel controlPanel;
    private GregorianCalendar calendar;

    public MainApplicationFrame(String title) {
        super(title);
        calendar = (GregorianCalendar) GregorianCalendar.getInstance();

        calendarTabbedPane = new JTabbedPane();
        yearPanel = new YearPanel(calendar);
        monthListPanel = new MonthListPanel(calendar);
        controlPanel = new ControlPanel(calendar);

        setupLayout();
        updatePanels();

        controlPanel.addPropertyChangeListener("monthChange", e -> {
            int newMonth = (int) e.getNewValue();
            calendar.set(Calendar.MONTH, newMonth);
            updatePanels();
        });

        controlPanel.addPropertyChangeListener("yearChange", e -> {
            int newYear = (int) e.getNewValue();
            calendar.set(Calendar.YEAR, newYear);
            updatePanels();
        });
    }

    private void setupLayout() {
        setLayout(new BorderLayout());
        add(calendarTabbedPane, BorderLayout.CENTER);
        add(controlPanel, BorderLayout.SOUTH);

        calendarTabbedPane.addTab("Year", yearPanel);
        calendarTabbedPane.addTab("Month", monthListPanel);
    }
    private void updateTabTitles() {
        SimpleDateFormat yearFormat = new SimpleDateFormat("yyyy", Locale.ENGLISH);
        SimpleDateFormat monthFormat = new SimpleDateFormat("MMMM", Locale.ENGLISH);

        String yearTitle = yearFormat.format(calendar.getTime());
        String monthTitle = monthFormat.format(calendar.getTime());

        calendarTabbedPane.setTitleAt(0, yearTitle); // Update Year tab title
        calendarTabbedPane.setTitleAt(1, monthTitle); // Update Month tab title
    }
    private void updatePanels() {
        yearPanel.updatePanel(calendar);
        monthListPanel.updatePanel(calendar);
        // Update titles, etc.
        updateTabTitles();
    }

    public void updateMonthListPanel(GregorianCalendar newCalendar) {
        monthListPanel.updatePanel(newCalendar);
    }

    // Other necessary methods...
}