n=int (input("Introduza um número: "))
soma=0
print ("Números divisíveis de ",n,":")

for i in range(1,n):
    if n%i==0:
        soma+=i
        print(i)

if soma>n:
    print ("O número ",n," é um número abundante!")
elif soma<n:
    print("O número ",n,"é deficiente!")
else:
    print("O número ",n," é um número perfeito!")