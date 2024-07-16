install.packages("gdata")
install.packages("arules")
library(gdata)
library(arules)

setwd("C:\\Users\\eduar\\Downloads\\MineracaodeDados")

# É necessário salvar os arquivos no diretório correspondente ao comando acima
# e definir a codificação UTF-8 para o arquivo _ASSOC_BGFriends_02.csv 

DF1 <- read.csv("./_ASSOC_BGFriends_01.csv")
DF2 <- read.csv("./_ASSOC_BGFriends_02.csv")
DF <- rbind(DF1, DF2)

# Garantir que não há partidas duplicadas
stopifnot(length(unique(DF$Partida)) == nrow(DF))

# Remover coluna de índice da partida
DF <- DF[, -1]

# Garantir o tamanho correto do DF unificado
stopifnot(nrow(DF1) + nrow(DF2) == nrow(DF))

# Separa a string por vírgulas e transforma em uma lista
DF$Jogadore.a.s <- strsplit(DF$Jogadore.a.s, split = ", ")

# Corta espaços em branco antes e depois dos nomes
DF$Jogadore.a.s <- lapply(DF$Jogadore.a.s, trim)

# Modifica nomes para que fiquem em letras minúsculas
DF$Jogadore.a.s <- lapply(DF$Jogadore.a.s, tolower)

# Corrige o nome francois para françois
corrigefrancois = function(nomes) {
  for (i in 1:length(nomes)) {
    if (nomes[[i]] == "francois") {
      nomes[[i]] = "françois"
    }
  }
  nomes
}
DF$Jogadore.a.s <- lapply(DF$Jogadore.a.s, corrigefrancois)

# Ordena o nome dos jogadores de cada linha para evitar
# que X, Y não seja considerado diferente de Y, X
DF$Jogadore.a.s <- lapply(DF$Jogadore.a.s, sort)

# Garantir nomes únicos de jogadores
stopifnot(length(levels(factor(unlist(DF$Jogadore.a.s)))) == 9)

# Garantir que não há valores extravagantes, que podem ser ruído
plot(DF$Amigos)
plot(DF$Oponentes)

# Remoção de empates
DF <- DF[DF$Amigos != DF$Oponentes, ]

# Criação de coluna que indica vitória
V <- DF$Amigos > DF$Oponentes

# Criação de coluna que indica derrota
D <- !V

# Criação de lista de presença dos jogadores
H <- sort(levels(factor(unlist(DF$Jogadore.a.s))))
P <- data.frame(matrix(ncol = length(H), nrow = 0))
colnames(P) <- H

for (i in 1:nrow(DF)) {
  v = vector()
  for (h in 1:length(H)) {
    for (j in 1:length(unlist(DF[i,"Jogadore.a.s"]))) {
      
      if (H[h] == unlist(DF[i,"Jogadore.a.s"])[j]) {
        v = c(v, TRUE)
        break
      } else if (j == length(unlist(DF[i,"Jogadore.a.s"]))) {
        v = c(v, FALSE)
      }
      
    }
  }
  P[nrow(P) + 1, ] = v
}

# Anexação de colunas de vitória e derrota na lista de presença
P <- cbind(P, vitoria = V, derrota = D)

# Definição de regras do melhor jogador 
rules1 <- apriori(P, parameter = list(target = "rules", confidence=0, support=0.1, maxlen=2))
rules1 <- sort(subset(rules1, (rhs %in% "vitoria")), by = "support")
inspect(rules1)

# Definição de regras da melhor equipe
rules2 <- apriori(P, parameter = list(target = "rules", confidence=0, support=0.1, minlen=3))
rules2 <- sort(subset(rules2, (rhs %in% "vitoria")), by = "support")
inspect(rules2)

# Definição de regras da pior equipe
rules3 <- apriori(P, parameter = list(target = "rules", confidence=0, support=0.1, minlen=3))
rules3 <- sort(subset(rules3, (rhs %in% "derrota")), by = "support")
inspect(rules3)

