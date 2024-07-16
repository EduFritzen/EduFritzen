Tema: diretores de cinema 
Nome: Luis henrique Pozzebon, Pedro Silva, Eduardo Fritzen.

Fonte URL:
https://www.the-numbers.com/box-office-star-records/worldwide/lifetime-specific-tech
nical-role/director

https://www.kaggle.com/datasets/danielgrijalvas/movies


Directors: Na tabela diretor temos 5 colunas das quais iremos explicar abaixo.
1)IdDirector - Um valor int para identificar os diretores/ IdDirector é chave primária da tabela directors
2)NameDirector - Um tipo varchar que armazena o nome do diretor.
3)Movies - que referência a tabela movies / Chave estrangeira
4)Avarege - Um tipo long que guarda a média de valores arrecadados nos filmes do diretor.

Movies: Na tabela filme temos 9 colunas das quais iremos explicar abaixo.
1) IdMove - Um valor int para identificar os filmes. / IdMovie é chave primária da tabela movies
2) NameMovie - Um tipo varchar que armazena o nome do filme.
3) Genre - Um tipo varchar que armazena o nome do gênero do filme.
4) YearMovie - Um valor int para guardar o ano de lançamento do filme.
5) Score - Um valor float para guardar a pontuação do filme.
6) IdDirector - que referência a tabela Directors  / Chave estrangeira
7) Writer - Um tipo varchar que contêm o nome do roteirista. 
8) Star - Um tipo varchar que contêm o nome do ator/atriz estrela do filme.
9) Company - Um tipo varchar que contêm  o nome da companhia/produtora do filme.