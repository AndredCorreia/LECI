def Fibonacci(n):
    F0=0
    F1=1
    
    if n==1:
        return(0)
    elif n==2:
        return(1)
        
        
    else:
        resultado=0
        for i in range (3,n+1):
            resultado=F0+F1
            F0=F1
            F1= resultado
        return resultado
        





def main():
    n= int(input("Introduza um número: "))
    print("O ",n,"º número de Fibonacci é ",Fibonacci(n))

if __name__ == "__main__":
    main()
