palavra= input("Introduza um nome: ")

def sigla(palavra):
    letras=[]
    for i in palavra:
        if i.isupper():
            letras.append(i)
    letras= "".join(letras)
    return letras


print(sigla (palavra))
print(sigla("Universidade de Aveiro"))
print(sigla("United Nations Organization"))