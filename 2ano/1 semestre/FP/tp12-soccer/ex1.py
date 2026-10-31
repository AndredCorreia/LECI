import csv
ficheiro="Soccer_Football_Clubs_Ranking.csv"
ficheiro_2="ficheiro100.txt"
def ler_clubes(ficheiro):
    """
    Lê o ficheiro CSV e devolve uma lista de tuplos, onde cada tuplo contém
    as informações de um clube.

    Args:
        ficheiro (str): Nome ou caminho do ficheiro CSV.

    Returns:
        list of tuple: Lista de tuplos com as informações de cada clube.
    """
    clubes = []
    try:
        with open(ficheiro, mode='r', encoding='utf-8') as f:
            leitor_csv = csv.reader(f)
            next(leitor_csv)  # Ignora o cabeçalho
            for linha in leitor_csv:
                # Converte os dados para os tipos adequados (inteiros, floats, etc.)
                posicao = int(linha[0])
                nome = linha[1]
                pais = linha[2]
                score_atual = float(linha[3])
                subida_descida = int(linha[4])
                score_anterior = float(linha[5])
                indicacao = linha[6]

                # Cria um tuplo com as informações da linha
                clube = (posicao, nome, pais, score_atual, subida_descida, score_anterior, indicacao)
                clubes.append(clube)
    except FileNotFoundError:
        print(f"Erro: O ficheiro '{ficheiro}' não foi encontrado.")
    except Exception as e:
        print(f"Erro ao processar o ficheiro: {e}")
    
    return clubes

def pais_clubes(country,ficheiro):
        with open(ficheiro, mode='r', encoding='utf-8') as f:
             leitor_csv= csv.reader(f)
             next(leitor_csv)
             clubes=[]
             for linha in leitor_csv:
                  if country == linha[2]:
                       clubes.append (f"{linha[1]},{linha[0]},{linha[3]}")

        return clubes

def escrever (country, ficheiro_2):
     with open(ficheiro_2,mode='w', encoding='utf-8') as f:
          f.writelines(pais_clubes(country,ficheiro))
               

def dicionario(clubes):
    dict={}
    for linha in clubes:
        if linha[2] not in dict:
            dict[linha[2]]= [linha[1]]
        else:
            dict[linha[2]].append(linha[1])
    return dict
               
def ranking(clubes):
    max= clubes[0][4]
    club= clubes[0]
    for linha in clubes:
          if max< linha[4]:
               max=linha[4]
               club= linha
    return(club)
    
def procura_clube(clube):
    i=0
    for linha in clubes:
          if clube in linha[1]:
               i=1
               return linha
    if i==0:
               return ("Não existe esse clube")
          
#def ranking_medio(clubes):
    
 #   pais_rank={}
 #   for linha in clubes:
 #       if linha[2] not in pais_rank:
 #           pais_rank[linha[2]]=[linha[0]]
 #       else:
 #           pais_rank[linha[2]].append(linha[0])
 #   for pais in pais_rank.keys():
 #       rankings= pais_rank[pais]
 #       media =0
 #       for i in range (0,len(rankings)):
 #           media+= rankings[i]
 #       print ("País: ",pais, "media: ",media/len(rankings))
def ranking_medio(clubes):
    pais_rank = {}
    
    # Organiza os rankings por país
    for linha in clubes:
        if linha[2] not in pais_rank:
            pais_rank[linha[2]] = [linha[0]]
        else:
            pais_rank[linha[2]].append(linha[0])

    # Calcula a média de ranking para cada país
    pais_media = {}
    for pais, rankings in pais_rank.items():
        media = sum(rankings) / len(rankings)
        pais_media[pais] = media

    # Ordena os países por ordem crescente de média
    pais_ordenados = sorted(pais_media.items(), key=lambda x: x[1])

    # Imprime os países e suas médias ordenados
    for pais, media in pais_ordenados:
        print(f'{pais}: {media:.2f}')


        
             
          



clubes=(ler_clubes(ficheiro))
#print (clubes)
#country=str(input ("Insira um país: "))
#print(pais_clubes(country, ficheiro))
#escrever(country,ficheiro_2)
#print(dicionario(clubes))
#print(ranking(clubes))
#clube= input("Introduza um clube: ")
#print(procura_clube(clube))
print(ranking_medio(clubes))
