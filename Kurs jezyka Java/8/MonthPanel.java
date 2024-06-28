package list08;

import javax.swing.*;
import java.awt.*;
import java.text.SimpleDateFormat;
import java.time.DayOfWeek;
import java.util.Calendar;
import java.util.GregorianCalendar;
import java.time.LocalDate;
import java.util.Locale;

public class MonthPanel extends JPanel {
    private final GregorianCalendar calendar;
    private DayPanel[] dayPanels;

    public MonthPanel(GregorianCalendar calendar) {
        this.calendar = (GregorianCalendar) calendar.clone();
        setupLayout();
    }

    private void setupLayout() {
        setLayout(new BorderLayout());
        SimpleDateFormat monthFormat = new SimpleDateFormat("MMMM", Locale.ENGLISH);
        JLabel monthLabel = new JLabel(monthFormat.format(calendar.getTime()), SwingConstants.CENTER);
        monthLabel.setFont(new Font(monthLabel.getFont().getName(), Font.BOLD, 16));
        add(monthLabel, BorderLayout.NORTH);

        JPanel daysPanel = new JPanel(new GridLayout(0, 7, 5, 5));
        dayPanels = new DayPanel[42];
        for (int i = 0; i < dayPanels.length; i++) {
            dayPanels[i] = new DayPanel(0, false, false);
            daysPanel.add(dayPanels[i]);
        }
        add(daysPanel, BorderLayout.CENTER);

        populateDays();
    }

    private void populateDays() {
        int year = calendar.get(Calendar.YEAR);
        int month = calendar.get(Calendar.MONTH);
        GregorianCalendar tempCalendar = new GregorianCalendar(year, month, 1);
        int firstDayOfWeekOfMonth = tempCalendar.get(Calendar.DAY_OF_WEEK);
        int startDayIndex = (firstDayOfWeekOfMonth == Calendar.SUNDAY) ? 6 : firstDayOfWeekOfMonth - 2;

        int daysInMonth = tempCalendar.getActualMaximum(Calendar.DAY_OF_MONTH);

        if (year == 1582 && month == Calendar.OCTOBER) {
            daysInMonth = 21;
        }

        for (int i = 0, day = 1; i < daysInMonth; i++, day++) {
            if (year == 1582 && month == Calendar.OCTOBER && day == 5) {
                day = 15;
            }
            tempCalendar.set(year, month, day);
            boolean isSunday = tempCalendar.get(Calendar.DAY_OF_WEEK) == Calendar.SUNDAY;
            boolean isToday = tempCalendar.equals(new GregorianCalendar());
            dayPanels[startDayIndex + i].setDay(day, isSunday, isToday);
        }
    }
}