# Complete o programa!

# a)
def loadFile(fname, lst):
    alunos=[]
    with open (fname,"r") as file:
        next(file)  
        for line in file:
            campos = line.strip().split('\t')  
            numero = int(campos[0])           
            nome = campos[1]                   
            nota1 = float(campos[5])             
            nota2 = float(campos[6])             
            nota3 = float(campos[7])             
            lst.append((numero, nome, nota1, nota2, nota3))

            

    ...
    
# b) Crie a função notaFinal aqui...
def notaFinal(lst):
    for aluno in lst:
        numero, nome, nota1, nota2, nota3 = aluno
        media = (nota1 + nota2 + nota3) / 3
        print(f"{nome} tem média de {media:.2f}")


# c) Crie a função printPauta aqui...
def printPauta(lst):
    
    print(f"{'Número':>0} {'Nome':^55} {'Nota Final':>0}")
    print("-" * 68)  

    for aluno in lst:
        numero, nome, nota1, nota2, nota3 = aluno
        media = (nota1 + nota2 + nota3) / 3  
        print(f"{numero:>0} {nome:^55} {media:>6.2f}")
    
   



# d)
def main():
    lst = []
    # ler os ficheiros
    loadFile("school1.csv", lst)
    loadFile("school2.csv", lst)
    loadFile("school3.csv", lst)
    
    # ordenar a lista
    notaFinal(lst)
    
    # mostrar a pauta
    printPauta(lst)

   
    



# Call main function
if __name__ == "__main__":
    main()


