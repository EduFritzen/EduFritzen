#!/usr/bin/env python
# coding: utf-8

# In[7]:


from collections import deque

def busca_profundidade(estado_inicial, objetivo, operadores):
    visitados = set()
    caminho = dfs(estado_inicial, objetivo, operadores, visitados)
    return caminho

def dfs(estado, objetivo, operadores, visitados):
    if estado == objetivo:
        return [estado]
    visitados.add(estado)
    for operador in operadores:
        novo_estado = operador[1](estado)
        if operador[0](novo_estado) and novo_estado not in visitados:
            caminho = dfs(novo_estado, objetivo, operadores, visitados)
            if caminho is not None:
                return [estado] + caminho
    return None

def busca_largura(estado_inicial, objetivo, operadores):
    visitados = set()
    fila = deque([(estado_inicial, [])])

    while fila:
        estado, caminho = fila.popleft()
        if estado == objetivo:
            return caminho + [estado]
        visitados.add(estado)
        for operador in operadores:
            novo_estado = operador[1](estado)
            if operador[0](novo_estado) and novo_estado not in visitados:
                fila.append((novo_estado, caminho + [estado]))

    return None


# Definição dos operadores
def vai(estado):
    return estado[1] != estado[2] and estado[2] != estado[3]

def levaLobo(estado):
    return estado[2] != estado[3]

def levaOvelha(estado):
    return Tru

def levaRepolho(estado):
    return estado[1] != estado[2]

def volta(estado):
    return estado[1] != estado[2] and estado[2] != estado[3]

def trazLobo(estado):
    return estado[2] != estado[3]

def trazOvelha(estado):
    return True

def trazRepolho(estado):
    return estado[1] != estado[2]

# Definição dos operadores
operadores = [
    (vai, lambda estado: ('d', estado[1], estado[2], estado[3])),
    (levaLobo, lambda estado: ('d', 'd', estado[2], estado[3])),
    (levaOvelha, lambda estado: ('d', estado[1], 'd', estado[3])),
    (levaRepolho, lambda estado: ('d', estado[1], estado[2], 'd')),
    (volta, lambda estado: ('e', estado[1], estado[2], estado[3])),
    (trazLobo, lambda estado: ('e', 'e', estado[2], estado[3])),
    (trazOvelha, lambda estado: ('e', estado[1], 'e', estado[3])),
    (trazRepolho, lambda estado: ('e', estado[1], estado[2], 'e'))
]

# Estado inicial e objetivo
estado_inicial = ('e', 'e', 'e', 'e')
estado_objetivo = ('d', 'd', 'd', 'd')

# Busca em profundidade
caminho_dfs = busca_profundidade(estado_inicial, estado_objetivo, operadores)
print("Caminho encontrado (Busca em Profundidade):", caminho_dfs)

# Busca em largura
caminho_bfs = busca_largura(estado_inicial, estado_objetivo, operadores)
print("Caminho encontrado (Busca em Largura):", caminho_bfs)


# In[24]:


from collections import deque

def busca_em_largura(inicio, objetivo, operadores):
    nos_abertos = deque([(inicio, [])])
    fechados = set()

    while nos_abertos:
        no, caminho = nos_abertos.popleft()
        fechados.add(no)

        if no == objetivo:
            return caminho + [no]

        for operador in operadores:
            if operador[1] == no and operador[2] not in fechados:
                nos_abertos.append((operador[2], caminho + [no]))

    return []

def busca_em_profundidade(inicio, objetivo, operadores):
    nos_abertos = [(inicio, [])]
    fechados = set()

    while nos_abertos:
        no, caminho = nos_abertos.pop()
        fechados.add(no)

        if no == objetivo:
            return caminho + [no]

        for operador in operadores:
            if operador[1] == no and operador[2] not in fechados:
                nos_abertos.append((operador[2], caminho + [no]))

    return []

# Lista de operadores
operadores = [
    (1, 'a', 'b'), (2, 'a', 'b'), (3, 'a', 'd'), (4, 'b', 'e'), (5, 'b', 'f'), (6, 'c', 'g'),
    (7, 'c', 'h'), (8, 'c', 'i'), (9, 'd', 'j'), (10, 'e', 'k'), (11, 'e', 'l'), (12, 'g', 'm'),
    (13, 'j', 'n'), (14, 'j', 'o'), (15, 'k', 'f'), (16, 'l', 'h'), (17, 'm', 'd'), (18, 'o', 'a'),
    (19, 'n', 'b')
]

# Questão a) - Algoritmo de busca em largura (BFS)
cidade_inicial = 'a'
cidade_objetivo = 'j'
caminho_bfs = busca_em_largura(cidade_inicial, cidade_objetivo, operadores)

if caminho_bfs:
    print("Caminho BFS:", ' -> '.join(caminho_bfs))
else:
    print("Não foi encontrado um caminho BFS entre as cidades.")

# Questão a) - Algoritmo de busca em profundidade (DFS)
caminho_dfs = busca_em_profundidade(cidade_inicial, cidade_objetivo, operadores)

if caminho_dfs:
    print("Caminho DFS:", ' -> '.join(caminho_dfs))
else:
    print("Não foi encontrado um caminho DFS entre as cidades.")


# In[25]:


from queue import Queue

def busca_em_largura(inicio, objetivo, operadores):
    nos_abertos = Queue()
    nos_abertos.put([inicio])  # Inicia com o nó inicial
    nodos_fechados = set()

    while not nos_abertos.empty():
        caminho = nos_abertos.get()
        estado_atual = caminho[-1]  # Último nó do caminho

        if estado_atual == objetivo:
            return caminho

        nodos_fechados.add(estado_atual)

        for operador in operadores:
            if operador[0] == estado_atual and operador[1] not in nodos_fechados:
                novo_caminho = caminho + [operador[1]]
                nos_abertos.put(novo_caminho)

    return None

def busca_em_profundidade(inicio, objetivo, operadores):
    nos_abertos = [[inicio]]  # Inicia com o nó inicial
    nodos_fechados = set()

    while nos_abertos:
        caminho = nos_abertos.pop()
        estado_atual = caminho[-1]  # Último nó do caminho

        if estado_atual == objetivo:
            return caminho

        nodos_fechados.add(estado_atual)

        for operador in operadores:
            if operador[0] == estado_atual and operador[1] not in nodos_fechados:
                novo_caminho = caminho + [operador[1]]
                nos_abertos.append(novo_caminho)

    return None

# Exemplo de uso
operadores = [
    ('a', 'b', 1), ('a', 'c', 9), ('a', 'd', 4),
    ('b', 'c', 7), ('b', 'e', 6), ('b', 'f', 1),
    ('c', 'f', 7), ('d', 'f', 4), ('d', 'g', 5),
    ('e', 'h', 9), ('f', 'h', 4), ('g', 'h', 1)
]

heuristica = {'a': 6, 'b': 5, 'c': 7, 'd': 7, 'e': 6, 'f': 4, 'g': 3, 'h': 0}

caminho_bl = busca_em_largura('a', 'h', operadores)
caminho_bp = busca_em_profundidade('a', 'h', operadores)
caminho_bg = busca_gulosa('a', 'h', operadores, heuristica)

print("Busca em Largura:", caminho_bl)
print("Busca em Profundidade:", caminho_bp)
print("Busca Gulosa:", caminho_bg)



# In[ ]:




