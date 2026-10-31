public class DateYMD {
    private int day;
    private int month;
    private int year;

    public DateYMD(int day, int month, int year) {
        if (!valid(day, month, year)) {
            throw new IllegalArgumentException("Data inválida.");
        }
        this.day = day;
        this.month = month;
        this.year = year;
    }

    public static boolean validMonth(int month) {
        return month >= 1 && month <= 12;
    }

    public static int monthDays(int month, int year) {
        if (month == 2) {
            return leapYear(year) ? 29 : 28;
        } else if (month == 4 || month == 6 || month == 9 || month == 11) {
            return 30;
        } else {
            return 31;
        }
    }

    public static boolean leapYear(int year) {
        return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
    }

    public static boolean valid(int day, int month, int year) {
        if (month < 1 || month > 12 || day < 1) {
            return false;
        }

        int maxDay = monthDays(month, year);
        return day <= maxDay;
    }

    public void set(int day, int month, int year) {
        if (!valid(day, month, year)) {
            throw new IllegalArgumentException("Data inválida.");
        }
        this.day = day;
        this.month = month;
        this.year = year;
    }

    public int getDay() {
        return day;
    }

    public int getMonth() {
        return month;
    }

    public int getYear() {
        return year;
    }

    public void increment() {
        day++;
        if (day > monthDays(month, year)) {
            day = 1;
            month++;
            if (month > 12) {
                month = 1;
                year++;
            }
        }
    }

    public void decrement() {
        day--;
        if (day < 1) {
            month--;
            if (month < 1) {
                month = 12;
                year--;
            }
            day = monthDays(month, year);
        }
    }

    
    public String toString() {
        return String.format("%04d-%02d-%02d", year, month, day);
    }

    public static void main(String[] args) {
        DateYMD date = new DateYMD(31, 12, 2022);
        System.out.println(date); // Saída: 2022-12-31
        date.increment();
        System.out.println(date); // Saída: 2023-01-01
        date.decrement();
        System.out.println(date); // Saída: 2022-12-31
    }
}
