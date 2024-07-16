drop database if exists integrado;
create database integrado;
use integrado;

create table Diretor(
	`idDiretor` int NOT NULL auto_increment,  # utiliza-se do auto-increment para inserir ids a partir do ultimo valor de outro banco
	`nomeDiretor` varchar(50) NOT NULL,
	`ganhosTotais` mediumtext,
	`numFilmes` int,
	`mediaGanhos` mediumtext,
	PRIMARY KEY(`idDiretor`)
);

insert into diretor(idDiretor, nomeDiretor, ganhosTotais, numFilmes, mediaGanhos)( # insere os diretores do banco de dados FILMES, 
	select * from filmes.directors												   # mantendo seu id original
);

insert into diretor(nomeDiretor)( # insere os diretores de DoctorWho, exceto sua coluna de id e nome, tudo eh NULL
	select concat ('"', Nome, '"') from doctorwho.diretor
);

create table Genero(
	`idGenero` int NOT NULL auto_increment,
    `nomeGenero` varchar(20) NOT NULL,
    PRIMARY KEY(`idGenero`)
);

insert into genero(idGenero, nomeGenero)( # insere os generos do banco de dados SAKILA
	select category_id, concat('"', `name`, '"') from sakila.category
);

insert into genero(nomeGenero)( # insere os generos do banco de dados FILMES que nao existam no SAKILA
	select distinct Genre 
    from filmes.movies
    where Genre not in (select concat('"', `name`, '"') 
					    from sakila.category)
);

create table Filmes(
	`idFilme` int NOT NULL auto_increment,
    `nomeFilme` varchar(60) NOT NULL,
    `idGenero` int,
    `score` float,
    `ano` int,
    `idDiretor` int,
    PRIMARY KEY(`idFilme`),
    FOREIGN KEY(`idDiretor`) references Diretor(`idDiretor`),
    FOREIGN KEY(`idGenero`) references Genero(`idGenero`)
);

insert into filmes(idFilme, nomeFilme, ano, idGenero)(  # insere os filmes do SAKILA, mantendo seus Ids originais
	select f.film_id, concat ('"', f.title, '"'), f.release_year, c.category_id 
    from sakila.film f , sakila.film_category c # no SAKILA, o Genero se relaciona com Filme por uma tabela propria
    where f.film_id = c.film_id					# pegamos os dados dessa tabela, e mesclamos na tabela Filmes
	order by f.film_id
);

insert into filmes(nomeFilme, score, ano, idDiretor, idGenero)( # insere os filmes do banco de dados FILMES
	select upper(m.NameMovie), m.Score, m.YearMovie, m.idDirector, i.idGenero
    from filmes.movies m join integrado.genero i on m.Genre like i.nomeGenero # utilizando de uma juncao, busca o id do Genero correspondente
	where upper(m.NameMovie) not in (select concat ('"', title, '"') # verifica se o filme ja nao foi inserido pelo SAKILA
									 from sakila.film)
);

create table Ator(
	`idAtor` int NOT NULL auto_increment,
    `nomeAtor` varchar(50) NOT NULL,
    PRIMARY KEY(`idAtor`)
);

insert into ator(idAtor, nomeAtor)( # insere os Atores do SAKILA, mantendo seu id original
	select actor_id, concat('"', first_name, ' ', last_name, '"') # concatena as colunas de nome e sobrenome
    from sakila.actor
);

insert into ator(nomeAtor)( # insere os Atores do FILMES
	select distinct upper(star) # no banco FILMES, Atores sao uma coluna da tabela Filme, logo, DISTINCT eh necessario, pois nomes se repetem
    from filmes.movies
    where upper(star) not in (select concat('"', first_name, ' ', last_name, '"')
							  from sakila.actor) # verifica se o Ator nao foi inserido pelo banco SAKILA
);

create table ParticipacaoFilme( # tabela que relaciona os Atores com Filmes
	`idAtor` int NOT NULL,
    `idFilme` int NOT NULL,
    PRIMARY KEY(`idAtor`, `idFilme`),
    FOREIGN KEY(`idAtor`) references Ator(`idAtor`),
    FOREIGN KEY(`idFilme`) references Filmes(`idFilme`)
);

insert into ParticipacaoFilme(idAtor, idFilme)( # insere os dados de uma tabela similar do SAKILA
	select actor_id, film_id  # ja que os ids dos Atores e Filmes se mantiveram os mesmos do SAKILA, a insercao eh mais facil
    from sakila.film_actor
);

insert into ParticipacaoFilme(idFilme, idAtor)( # insere os dados referentes ao banco FILMES
	select f.idFilme, a.idAtor  
    from filmes f, ator a # seleciona dados de Filmes e Atores do banco de dados integrado
    where (f.nomeFilme, a.nomeAtor) in (select upper(NameMovie), upper(star) # verifica se essa tupla de dados esta na mesma linha da tabela MOVIES
										from filmes.movies m)		 		 # do banco FILMES
);