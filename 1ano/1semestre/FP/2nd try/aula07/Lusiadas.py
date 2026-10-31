import time
start_time= time.time()
def contar_caracteres(texto):
    contagem = {}

    for linha in texto:
        linha=linha.lower()
        for c in linha:
            if c.isalpha():
                if c in contagem:
                    contagem[c] += 1
                else:
                    contagem[c] = 1

    return contagem


with open ("/home/andre/Desktop/Universidade/2ano/1 semestre/FP/aula07/examples/pg3333.txt","r", encoding="utf-8") as text:
    conteudo = text.readlines()
    letras=0
    for linha in text:
        print(linha)
        for c in linha:
            if c.isalpha():
                letras+=1
        
    print (letras)

    contagem_caracteres = contar_caracteres(conteudo)
    print("\nFrequência de cada caractere:")
    for caractere, quantidade in sorted(contagem_caracteres.items()):
        print(f"'{caractere}': {quantidade}")
    end_time= time.time()
    elapsed_time= end_time - start_time
    print(elapsed_time)

    