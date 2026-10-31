def inputFloatList():
    lista=[]
    while  True :
        n= input ("Insira um numero: ")
        if n=="":
            break
        try:
            lista.append(int(n))
        except ValueError:
            print("Por favor, insira um número válido.")
    
    
    
    print (lista)
    return (lista)


def countLower(lista):
    menores=0
    v=input("Introduza um valor que deseje comparar com os números da lista: ")
    
    for i in lista:
        if i<int(v):
            menores+=1  
    return(menores)  

def minMax(lista):
    minimo=lista[0]
    maximo=lista[0]

    for i in lista:
        if i<minimo:
            minimo=i
        if i>maximo:
            maximo=i
    
    print("O número maior é ", maximo)
    print ("O número menor é ", minimo)

    valor_medio= (maximo+minimo)/2
    num_menores= 0
    lista_menores=[]
    for i in lista:
        if i<valor_medio:
            num_menores+=1
            lista_menores.append(i)
    print ("O número de valores menores que ", valor_medio," é ", num_menores," sendo eles: ",lista_menores,"!")


    

def main():
    lista=inputFloatList()
    resultado=countLower(lista)
    print ("Existem ", resultado," números menores que o valor inserido")
    minMax(lista)
    

main()

