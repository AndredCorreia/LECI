equipas=["FCPorto","SLBenfica","SCP","Braga","Arouca"]
jogos=[]
for i in equipas:
    for j in equipas:
        if i!=j:
            jogos.append((i,j))
print (jogos)