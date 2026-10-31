package aula07;


public abstract class Date {
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

    public abstract void incrementar(int dias);
    public abstract void decrementar(int dias);
    public abstract void set(int day, int month, int year);
}

