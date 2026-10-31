with open('names.txt', 'r') as nomes:
    dicionario = {}
    
    for linha in nomes:
        s = linha.strip().split(" ")
        ap = s[-1]  
        pn = s[0]   

        if ap not in dicionario:
            dicionario[ap] = set() 
            print(dicionario) 

        dicionario[ap].add(pn)

    print(dicionario)
