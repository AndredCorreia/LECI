package aula07;

class DateYMD extends Date {
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

    @Override
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

    @Override
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

    @Override
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
        return String.format("%02d/%02d/%04d", day, month, year);
    }

    public int getDay(){
        return this.day;
    }
    public int getMonth(){
        return this.month;
    }
    public int getYear(){
        return this.year;
    }
}
