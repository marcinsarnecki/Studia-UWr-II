package list08;

import javax.swing.*;
import java.awt.*;
import java.util.Calendar;
import java.util.GregorianCalendar;

public class MonthListPanel extends JPanel {
    private int year, month;

    public MonthListPanel(GregorianCalendar calendar) {
        this.year = calendar.get(Calendar.YEAR);
        this.month = calendar.get(Calendar.MONTH);
        setLayout(new GridLayout(1, 3, 10, 10));
        setupLists();
    }

    private void setupLists() {
        removeAll();

        JList<String> previousMonthList = createMonthList(-1, false);
        JList<String> currentMonthList = createMonthList(0, true);
        JList<String> nextMonthList = createMonthList(1, false);

        addListWithScrollPane(previousMonthList);
        addListWithScrollPane(currentMonthList);
        addListWithScrollPane(nextMonthList);

        revalidate();
        repaint();
    }
    private void addListWithScrollPane(JList<String> monthList) {
        JScrollPane scrollPane = new JScrollPane(monthList);
        scrollPane.setBorder(BorderFactory.createEmptyBorder(5, 5, 5, 5)); // Adding padding around the list

        JPanel panel = new JPanel(new BorderLayout());
        panel.add(scrollPane, BorderLayout.CENTER);

        add(panel);
    }

    private JList<String> createMonthList(int monthOffset, boolean isCurrentMonth) {
        int adjustedMonth = (month + monthOffset) % 12;
        int adjustedYear = year + ((month + monthOffset) / 12);
        if (adjustedMonth < 0) {
            adjustedMonth += 12;
            adjustedYear -= 1;
        }

        MonthListModel model = new MonthListModel(adjustedYear, adjustedMonth);
        JList<String> monthList = new JList<>(model);
        monthList.setCellRenderer(new DayCellRenderer());

        if (isCurrentMonth) {
            monthList.setBackground(Color.WHITE);
        } else {
            monthList.setBackground(Color.LIGHT_GRAY);
        }

        return monthList;
    }

    public void updatePanel(GregorianCalendar newCalendar) {
        this.year = newCalendar.get(Calendar.YEAR);
        this.month = newCalendar.get(Calendar.MONTH);
        setupLists();
    }
    private static class DayCellRenderer extends DefaultListCellRenderer {
        @Override
        public Component getListCellRendererComponent(JList<?> list, Object value, int index, boolean isSelected, boolean cellHasFocus) {
            super.getListCellRendererComponent(list, value, index, isSelected, cellHasFocus);
            setHorizontalAlignment(SwingConstants.CENTER); // Center alignment

            if (value.toString().contains("Sun")) {
                setForeground(Color.RED);
            } else {
                setForeground(Color.BLACK);
            }
            return this;
        }
    }
}
