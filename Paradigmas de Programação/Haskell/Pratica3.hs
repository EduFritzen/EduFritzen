--1.Usando list comprehension, defina uma função add10toall :: [Int] -> [Int], que receba uma lista e adicione o valor 10 a cada elemento dessa lista, produzindo outra lista. Exemplo:
add10toall :: [Int] -> [Int]
add10toall x = [x + 10 | x <- x] 

--2.Usando list comprehension, defina uma função multN :: Int -> [Int] -> [Int], que receba um número N e uma lista, e multiplique cada elemento da lista por N, produzindo outra lista.
multN :: Int -> [Int] -> [Int]
multN n l = [n*l | l <- l]

--3.Usando a função de alta ordem map, defina a função multN' :: Int -> [Int] -> [Int], equivalente à função do exercício anterior.
multN' :: Int -> [Int] -> [Int]
multN' n l = map (\l -> n*l) l

--4.Usando list comprehension, defina uma função applyExpr :: [Int] -> [Int], que receba uma lista e calcule 3*x+2 para cada elemento x da lista, produzindo outra lista.
applyExpr :: [Int] -> [Int]
applyExpr l = [3*l+2 | l <- l] 

--5.Reescreva a função do exercício anterior usando lambda e uma função de alta ordem. A assinatura da função será applyExpr' :: [Int] -> [Int].
applyExpr' :: [Int] -> [Int]
applyExpr' l = map (\l -> 3*l+2) l

--6.Usando list comprehension, escreva uma função addSuffix :: String -> [String] -> [String] , para adicionar um dado sufixo às strings contidas numa lista. Exemplo:
addSuffix :: String -> [String] -> [String]
addSuffix s ss = [ss++s | ss <- ss]

--7.Usando list comprehension, defina uma função selectgt5 :: [Int] -> [Int], que receba uma lista e selecione somente os valores maiores que 5, produzindo outra lista.
selectgt5 :: [Int] -> [Int]
selectgt5 l = [l |l <- l, l>5]

--8.Usando list comprehension, defina uma função sumOdds :: [Int] -> Int, que receba uma lista e obtenha o somatório dos valores ímpares, produzindo outra lista. Para auxiliar nesta função, você deverá pesquisar funções pré-definidas em Haskell.
sumOdds :: [Int] -> Int
sumOdds l = sum([l | l <- l, odd l])

--9.Resolva a questão anterior sem usar list comprehension, criando a função sumOdds' :: [Int] -> Int.
auxSumOdds' :: Int -> Int
auxSumOdds' l = if odd l then l else 0
sumOdds' :: [Int] -> Int
sumOdds' l = sum (map  auxSumOdds' l) 

--10.Usando list comprehension, defina uma função selectExpr :: [Int] -> [Int], que receba uma lista e selecione somente os valores pares entre 20 e 50, inclusive, produzindo outra lista.
selectExpr :: [Int] -> [Int]
selectExpr l = [l |l <- l, l>20 && l<50 && even l]

--11.Escreva uma função countShorts :: [String] -> Int, que receba uma lista de palavras e retorne a quantidade de palavras dessa lista que possuem menos de 5 caracteres. Use list comprehension.
countShorts :: [String] -> Int
countShorts ss = length([ss | ss <- ss, length ss < 5])

--12.Escreva uma função calcExpr :: [Float] -> [Float], que calcule x^2/2 para cada elemento x da lista de entrada e selecione apenas os resultados que forem maiores que 10. Use list comprehension.
calcExpr :: [Float] -> [Float]
calcExpr res = [(l*l)/2 | l <- res, ((l*l)/2)>10]

--13.Escreva uma função trSpaces :: String -> String, que receba uma string e converta espaços (' ') em traços ('-'). Use list comprehension.
trSpaces :: String -> String
trSpaces str = [if c == ' ' then '-' else c | c <- str]

--14.Usando list comprehension, Defina uma função selectSnd :: [(Int,Int)] -> [Int], que receba uma lista de tuplas e selecione somente os segundos elementos dessas tuplas, produzindo outra lista. 
selectSnd :: [(Int,Int)] -> [Int]
selectSnd l = [ l2 | (l1, l2) <- l]

--15.Em Haskell, a função zip combina elementos de duas listas, produzindo uma lista de tuplas. Usando a função zip com list comprehension e outras funções auxiliares, escreva uma função dotProd :: [Int] -> [Int] -> Int que calcule o somatório dos produtos dos pares de elementos de duas listas.
dotProd :: [Int] -> [Int] -> Int
dotProd xs ys = sum [x * y|(x, y) <- zip xs ys]