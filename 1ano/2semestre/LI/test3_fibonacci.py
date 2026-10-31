import sys
def fibonaccy(n):
    n= int(n)
    res=[]
    if n<0:
        return res
    
    elif n==0 :
        res=[0]
        return res
    else :
        res=[0,1]
        for i in range (2,n+1):
            res.append(res[i-2]+res[i-1])
        return res


#n= input ("Insira um número!")
#print(fibonacci(n))

            
            


def usage(progname):
    print("Usage: python3 %s positive number" % (progname))


def main(argv):
    if(len(argv) != 2):
        usage(argv[0])
        sys.exit(1)

    if not argv[1].isdigit():
        usage(argv[0])
        sys.exit(2)
    print(fibonaccy(int(argv[1])))
    sys.exit(0)


if __name__ == "__main__":
    main(sys.argv)

