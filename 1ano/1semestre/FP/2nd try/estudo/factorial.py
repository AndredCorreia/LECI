def calcular_fatorial(n):
    if n < 0:
        return "Fatorial não é definido para números negativos."
    elif n == 0 or n == 1:
        return str(n) + "! = 1 "
    
    fatorial = 1
    calculo = str(n) + "!"
    for i in range(n, 0, -1):
        fatorial *= i
        if i != n:
            calculo += " x " + str(i)
        else:
            calculo += " = " + str(i)
    
    return calculo + " = " + str(fatorial)

numero = int(input("Digite um número para calcular o fatorial: "))
resultado = calcular_fatorial(numero)
print(resultado)


