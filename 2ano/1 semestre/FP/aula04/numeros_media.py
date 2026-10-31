sequencia= (input("introduza um número: "))
if sequencia =="":
    print ("Não introduziu nenhum número!")
else:
    soma=0
    i=0
    while sequencia!="":
        soma+=int(sequencia)
        i+=1
        sequencia= (input("Introduza outro número: "))

    media= soma/i
    print("Introduziu um total de ",i," números, e a sua média é ", media)

    

