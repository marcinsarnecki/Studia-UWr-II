package list08;

import javax.swing.AbstractListModel;
import java.text.SimpleDateFormat;
import java.util.Calendar;
import java.util.Locale;

public class MonthListModel extends AbstractListModel<String> {
    private int year;
    private int month;

    public MonthListModel(int year, int month) {
        this.year = year;
        this.month = month;
        updateDaysInMonth();
    }

    private void updateDaysInMonth() {
        Calendar tempCalendar = Calendar.getInstance();
        tempCalendar.set(Calendar.YEAR, year);
        tempCalendar.set(Calendar.MONTH, month);
    }

    @Override
    public int getSize() {
        if (year == 0)
            return 0;
        if (year == 1582 && month == 9)
            return 21;
        Calendar cal = Calendar.getInstance();
        cal.set(year, month, 1);
        return cal.getActualMaximum(Calendar.DAY_OF_MONTH);
    }

    @Override
    public String getElementAt(int index) {
        Calendar tempCalendar = Calendar.getInstance();
        tempCalendar.set(Calendar.YEAR, year);
        tempCalendar.set(Calendar.MONTH, month);
        tempCalendar.set(Calendar.DAY_OF_MONTH, index + 1);
        SimpleDateFormat dateFormat = new SimpleDateFormat("MMMM d EEE", Locale.ENGLISH);
        return dateFormat.format(tempCalendar.getTime());
    }

    public void setYearAndMonth(int year, int month) {
        this.year = year;
        this.month = month;
        updateDaysInMonth();
        fireContentsChanged(this, 0, getSize() - 1);
    }
}