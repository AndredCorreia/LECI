
def parseMDY(date):
    """Return (year, month, day) from date in MM/DD/YYYY format."""
    date= (date).split("/")
    if (len(date)==1):
        new_date= int(date[0]),0,0 
        return (new_date)
    else:
        
        date= [int(x) for x in date]
        return date[2],date[0],date[1]

def yearsBetween(date1, date2):
    """Return integer number of years between two (y, m, d) dates."""
    year1= int(date1[0])
    year2= int (date2[0])
    
    if date1[1]== date2[1] and date1[2]==date2[2]:
        return year2-year1
    else:
        if date1[1]>date2[1]:
            return year2-year1-1
        elif date1[1]<date2[1]:
            return year2-year1+1
        else:
            if date1[2]<date2[2]:
                return year2-year1+1
            else:
                return year2-year1-1


def main():
    # Test parseMDY
    print(f"{parseMDY('12/25/2024') = }")  # (2024, 12, 25)
    print(f"{parseMDY('4/25/1974') = }")   # (1974, 4, 25)
    print(f"{parseMDY('1755') = }")        # (1755, 0, 0)

    # Test yearsBetween
    print(f"{yearsBetween((1900, 6, 1), (1935, 5, 31)) = }")  # 34
    print(f"{yearsBetween((1900, 6, 1), (1935, 6, 1)) = }")   # 35
    print(f"{yearsBetween((1900, 6, 1), (1936, 5, 31)) = }")  # 35


# This program may be used as a module too
if __name__ == "__main__":
    main()

