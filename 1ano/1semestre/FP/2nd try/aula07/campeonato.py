def gerar_jogos(equipas):
    jogos = []
    for i in range(len(equipas)):
        for j in range(i + 1, len(equipas)):
            jogos.append((equipas[i], equipas[j]))
    return jogos

def atualizar_tabela(tabela, resultado, jogo):
    equipa1, equipa2 = jogo
    golos1, golos2 = resultado

    if golos1 > golos2:
        tabela[equipa1][0] += 1 
        tabela[equipa2][2] += 1  
        tabela[equipa1][4] += golos1  
        tabela[equipa1][5] += golos2  
        tabela[equipa2][4] += golos2  
        tabela[equipa2][5] += golos1  
        tabela[equipa1][6] += 3  
    elif golos1 < golos2:
        tabela[equipa2][0] += 1  
        tabela[equipa1][2] += 1  
        tabela[equipa2][4] += golos2  
        tabela[equipa2][5] += golos1  
        tabela[equipa1][4] += golos1  
        tabela[equipa1][5] += golos2  
        tabela[equipa2][6] += 3  
    else:
        tabela[equipa1][1] += 1  
        tabela[equipa2][1] += 1  
        tabela[equipa1][4] += golos1   
        tabela[equipa1][5] += golos2  
        tabela[equipa2][4] += golos2  
        tabela[equipa2][5] += golos1  
        tabela[equipa1][6] += 1 
        tabela[equipa2][6] += 1  

def determinar_campeao(tabela):
    campeao = None
    max_pontos = -1
    melhor_diferenca = -1
    for equipa, registos in tabela.items():
        pontos = registos[6]
        diferenca_golos = registos[4] - registos[5]  # Golos marcados - Golos sofridos
        if pontos > max_pontos or (pontos == max_pontos and diferenca_golos > melhor_diferenca):
            campeao = equipa
            max_pontos = pontos
            melhor_diferenca = diferenca_golos
    return campeao

def campeonato():
    equipas = []
    num_equipas = int(input("Quantas equipas participam no campeonato? "))
    for i in range(num_equipas):
        nome_equipa = input(f"Nome da equipa {i + 1}: ")
        equipas.append(nome_equipa)

    
    jogos = gerar_jogos(equipas)

    resultados = {}
    for jogo in jogos:
        print(f"\nResultado do jogo entre {jogo[0]} e {jogo[1]}:")
        golos1 = int(input(f"Quantos golos marcou {jogo[0]}? "))
        golos2 = int(input(f"Quantos golos marcou {jogo[1]}? "))
        resultados[jogo] = (golos1, golos2)

    tabela = {equipa: [0, 0, 0, 0, 0, 0, 0] for equipa in equipas}  
    
    for jogo, resultado in resultados.items():
        atualizar_tabela(tabela, resultado, jogo)

    print("\nTabela Classificativa:")
    print(f"{'Equipa':<15}{'V':<3}{'E':<3}{'D':<3}{'GM':<4}{'GS':<4}{'Pontos':<7}")
    for equipa, registos in tabela.items():
        print(f"{equipa:<15}{registos[0]:<3}{registos[1]:<3}{registos[2]:<3}{registos[4]:<4}{registos[5]:<4}{registos[6]:<7}")

    campeao = determinar_campeao(tabela)
    print(f"\nA equipa campeã é: {campeao}")

campeonato()
