numero= input("Introduza um número: ")
lista=[]
lista.append(numero)
while numero!= "" :
    numero= input("Introduza um número: ")
    lista.append(numero)
media=0
lista.remove(lista[-1])
#print(lista)
lista= [int(x) for x in lista]
for i in range(0,len(lista)):
    media+=lista[i]

media= media/len(lista)

print ("A média dos números introduzidos é: ", media)
print(lista)

