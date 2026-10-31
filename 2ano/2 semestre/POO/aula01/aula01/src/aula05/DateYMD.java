package aula05;

public class DateYMD {
    private int day, month, year;
    
    public DateYMD(int day, int month, int year) {
        if (valid(day, month, year)) {
            this.day = day;
            this.month = month;
            this.year = year;
        } else {
            throw new IllegalArgumentException("Data inválida!");
        }
    }

    public void incrementar(int dias) {
        for (int i = 0; i < dias; i++) {
            this.day++;
            if (this.day > monthDays(this.month, this.year)) {
                this.day = 1;
                this.month++;
                if (this.month > 12) {
                    this.month = 1;
                    this.year++;
                }
            }
        }
    }

    public void decrementar(int dias) {
        for (int i = 0; i < dias; i++) {
            this.day--;
            if (this.day < 1) {
                this.month--;
                if (this.month < 1) {
                    this.month = 12;
                    this.year--;
                }
                this.day = monthDays(this.month, this.year);
            }
        }
    }

    public void set(int day, int month, int year) {
        if (valid(day, month, year)) {
            this.day = day;
            this.month = month;
            this.year = year;
        } else {
            System.out.println("Data inválida!");
        }
    }

    @Override
    public String toString() {
        return String.format("%d/%d/%d", day, month, year);
    }

    public static boolean leapYear(int year) {
        return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
    }

    public static boolean valid(int day, int month, int year) {
        if (month < 1 || month > 12) return false;
        int maxDays = monthDays(month, year);
        return (day > 0 && day <= maxDays);
    }

    public static int monthDays(int month, int year) {
        return switch (month) {
            case 2 -> (leapYear(year) ? 29 : 28);
            case 4, 6, 9, 11 -> 30;
            default -> 31;
        };
    }
}
