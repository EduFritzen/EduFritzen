#!/usr/bin/env python3
from math import inf as infinito
from random import choice
import platform
from os import system

HUMANO = -1
IA = +1
tabuleiro = [
    [0, 0, 0, 0],
    [0, 0, 0, 0],
    [0, 0, 0, 0],
    [0, 0, 0, 0]
]

def verifica_vencedor(estado, player): 

    estado_vitoria = [
        [estado[0][0], estado[0][1], estado[0][2], estado[0][3]],
        [estado[1][0], estado[1][1], estado[1][2], estado[1][3]],
        [estado[2][0], estado[2][1], estado[2][2], estado[2][3]],
        [estado[3][0], estado[3][1], estado[3][2], estado[3][3]],
        [estado[0][0], estado[1][0], estado[2][0], estado[3][0]],
        [estado[0][1], estado[1][1], estado[2][1], estado[3][1]],
        [estado[0][2], estado[1][2], estado[2][2], estado[3][2]],
        [estado[0][3], estado[1][3], estado[2][3], estado[3][3]],
        [estado[0][0], estado[1][1], estado[2][2], estado[3][3]],
        [estado[3][0], estado[2][1], estado[1][2], estado[0][3]]
    ]
    if [player, player, player] in estado_vitoria:
        return True
    else:
        return False

def game_over(estado):
    if verifica_vencedor(estado, HUMANO):
        return True
    elif verifica_vencedor(estado, IA):
        return True
    else:
        return False

def posicoes_vazias(estado): # retorna uma lista de células vazias

    celulas = []
    for x, linha in enumerate(estado):
        for y, celula in enumerate(linha):
            if celula == 0:
                celulas.append([x, y])
    return celulas

def define_movimento(x, y, player): 

    if [x, y] in posicoes_vazias(tabuleiro): # Verifica se uma jogada é válida
        tabuleiro[x][y] = player
        return True
    else:
        return False

def avalia_estado(estado): 
    if verifica_vencedor(estado, IA): return +1 # IA ganhou
    elif verifica_vencedor(estado, HUMANO): return -1 # PLAYER ganhou
    else: return 0 # Empate

def limpa_tela():
    if 'windows' in (platform.system().lower()):
        system('cls')
    else:
        system('clear')

def imprime_tabuleiro(estado, escolha_ia, escolha_h): # Printa o tabuleiro atualizado

    chars = {
        -1: escolha_h,
        +1: escolha_ia,
        0: ' '
    }
    linha_separadora = '--------------------'

    print('\n' + linha_separadora)
    for linha in estado:
        for celula in linha:
            simbolo = chars[celula]
            print(f'| {simbolo} |', end='')
        print('\n' + linha_separadora)

def minimax(estado, profundidade, player):

    if player == IA:
        melhor = [-1, -1, -infinito] # inicia com o pior score
    else:
        melhor = [-1, -1, +infinito] # inicia com o pior score

    if profundidade == 0 or game_over(estado):
        score = avalia_estado(estado)
        return [-1, -1, score]

    for celula in posicoes_vazias(estado): # Para cada movimento válido
        x = celula[0] 
        y = celula[1]
        estado[x][y] = player
        score = minimax(estado, profundidade - 1, -player)
        estado[x][y] = 0
        score[0], score[1] = x, y

        if player == IA:
            if score[2] > melhor[2]:
                melhor = score  # max value
        else:
            if score[2] < melhor[2]:
                melhor = score  # min value

    return melhor

def verfica_tabuleiro(profundidade): # Verifica se é possível fazer jogadas ou não
    if profundidade == 0 or game_over(tabuleiro):
        return
    
def jogada_ia(escolha_ia, escolha_h):

    profundidade = len(posicoes_vazias(tabuleiro))
    verfica_tabuleiro(profundidade)

    limpa_tela()
    print(f'Vez do computador [{escolha_ia}]')
    imprime_tabuleiro(tabuleiro, escolha_ia, escolha_h)

    if profundidade == 16: # primeira jogada da IA
        x = choice([0, 1, 2, 3])
        y = choice([0, 1, 2, 3])
    else:
        movimento = minimax(tabuleiro, profundidade, IA)
        x, y = movimento[0], movimento[1]

    define_movimento(x, y, IA)

def jogada_h(escolha_ia, escolha_h):

    profundidade = len(posicoes_vazias(tabuleiro))
    verfica_tabuleiro(profundidade)

    movimento = -1
    movimentos = {
        1: [0, 0], 2: [0, 1], 3: [0, 2], 4: [0, 3],
        5: [1, 0], 6: [1, 1], 7: [1, 2], 8: [1, 3],
        9: [2, 0], 10: [2, 1], 11: [2, 2], 12: [2, 3],
        13: [3, 0], 14: [3, 1], 15: [3, 2], 16: [3, 3],
    }

    limpa_tela()
    print(f'Sua vez! [{escolha_h}]')
    imprime_tabuleiro(tabuleiro, escolha_ia, escolha_h)

    while movimento < 1 or movimento > 16:
        movimento = int(input('Digite o número da célula em que deseja jogar (1-16): '))
        coordenadas = movimentos[movimento]
        pode_mover = define_movimento(coordenadas[0], coordenadas[1], HUMANO)

        if not pode_mover:
            print('Tente novamente')
            movimento = -1

def resultado_jogo(tabuleiro, escolha_ia, escolha_h):
    if verifica_vencedor(tabuleiro, HUMANO):
        print('Você venceu!')
    elif verifica_vencedor(tabuleiro, IA):
        print('Você Perdeu!')
    else:
        print('Empate!')
    imprime_tabuleiro(tabuleiro, escolha_ia, escolha_h)

def main():

    limpa_tela()
    escolha_h = ''  
    escolha_ia = '' 
      
    while escolha_h != 'O' and escolha_h != 'X':
        escolha_h = input('Escolha X ou O\nEscolha: ').upper()

    if escolha_h == 'X':
        escolha_ia = 'O'
    else:
        escolha_ia = 'X'

    limpa_tela() #Decide quem começa
    first = ''
    while first != 'S' and first != 'N':
        first = input('Começar primeiro?[s/n]: ').upper()

    while len(posicoes_vazias(tabuleiro)) > 0 and not game_over(tabuleiro): #Executa até acabar o jogo
        if first == 'N':
            jogada_ia(escolha_ia, escolha_h)
            first = ''

        jogada_h(escolha_ia, escolha_h)
        jogada_ia(escolha_ia, escolha_h)

    limpa_tela()

    resultado_jogo(tabuleiro, escolha_ia, escolha_h)

    exit()

if __name__ == '__main__':
    main()