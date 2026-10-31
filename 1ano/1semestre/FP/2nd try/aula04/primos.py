def isPrime():
    for i in range (2,101):
        if i==2 or i==3 or i==5 or i==7:
            print ("",i," é um número primo")
        elif i%2!=0 and i%3!=0 and i%5!=0 and i%7!=0:
            print (i," é um número primo")

def main():
    isPrime()


if __name__=="__main__":
    main()             