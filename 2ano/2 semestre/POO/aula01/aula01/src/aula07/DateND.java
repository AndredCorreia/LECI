package aula07;

public class DateND extends Date{
    private int diasDesde2000;

    public DateND(int dias){
        if (dias>=0){
            this.diasDesde2000=dias;
        }
        else{
            throw new IllegalArgumentException("Número de dias inválido!");
        }
    }

    public DateYMD toDateYMD(){
        int year=2000;
        int month=1;
        int day=1;

        while(this.diasDesde2000>0){
            int daysInMonth = monthDays(month, year);
            if (this.diasDesde2000 < daysInMonth) {
                day += this.diasDesde2000;
                break;
            } else {
                this.diasDesde2000 -= daysInMonth;
                month++;
                if (month > 12) {
                    month = 1;
                    year++;
                }
            }
        }

        return new DateYMD(day, month, year);
    }
    @Override
    public void incrementar(int dias) {
        this.diasDesde2000 += dias;
    }

    @Override
    public void decrementar(int dias) {
        if (this.diasDesde2000 - dias < 0) {
            throw new IllegalArgumentException("Não é possível decrementar além da data 1º de Janeiro de 2000");
        }
        this.diasDesde2000 -= dias;
    }    
    
    @Override
    public void set(int day, int month, int year) {
        DateYMD dateYMD = new DateYMD(day, month, year);
        this.diasDesde2000 = dateYMDToDays(dateYMD);
    }
    private int dateYMDToDays(DateYMD date) {
        int totalDays = 0;
        int year = date.getYear();
        int month = date.getMonth();
        int day = date.getDay();

        while (year > 2000) {
            totalDays += (leapYear(year) ? 366 : 365);
            year--;
        }

        for (int m = 1; m < month; m++) {
            totalDays += monthDays(m, year);
        }

        totalDays += day - 1;  

        return totalDays;
    }

    @Override
    public String toString() {
        return String.format("%d dias desde 01/01/2000", this.diasDesde2000);
    }

    @Override
    public boolean equals(Object obj) {
        if (this == obj) return true;
        if (obj == null || getClass() != obj.getClass()) return false;
        DateND dateND = (DateND) obj;
        return diasDesde2000 == dateND.diasDesde2000;
    }
}



