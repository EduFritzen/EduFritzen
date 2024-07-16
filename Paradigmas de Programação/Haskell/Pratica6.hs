--1.Escreva uma função ends :: [Int] -> [Int] que receba uma lista e retorne outra lista contendo o primeiro e o último elementos da primeira lista. Use o operador de construção de lista (:).
ends :: [Int] -> [Int]
ends l = head l : last l : []

--2.Reescreva a função deduzame do Aquecimento usando a notação (x:xs) para representar a lista lst. Ajuste o restante do código da função. Você verá que o código ficará mais enxuto.
deduzame :: [Integer] -> [Integer]
deduzame []=[]
deduzame (x:xs) = (2*x) : deduzame xs

--3.Reescreva também a função deduzame2 do Aquecimento, usando a notação (x:xs) para representar a lista lst.
deduzame2 :: [Integer] -> [Integer]
deduzame2 [] = []
deduzame2 (x:xs) = if x> 2
    then x : deduzame2 xs
    else deduzame2 xs

--4.Usando recursão, escreva uma função geraTabela :: Int -> [(Int,Int)] que produza uma lista com n tuplas, cada tupla com números de n a 1 e seus respectivos quadrados. Exemplo:
geraTabela :: Int -> [(Int,Int)]
geraTabela 0 = []
geraTabela n = (n, n*n) : geraTabela (n-1)

--5.Defina uma função recursiva que verifique se um dado caracter está contido numa string, conforme os exemplos abaixo:
contido :: Char -> String -> Bool 
contido c [] = False
contido c str = if (head str == c) then True else contido c (tail str)

--6.Defina uma função recursiva translate, que receba uma lista de coordenadas de pontos 2D e desloque esses pontos em 2 unidades. 
translate :: [(Float,Float)] -> [(Float,Float)]
translate [] = []
translate ((x,y):xs) = (x+2,y+2) : translate xs

--7.Defina uma função recursiva countLongs, que receba uma lista de palavras e retorne a quantidade dessas palavras que tenham mais de 5 caracteres. A tipagem da função é por sua conta! Exemplo de uso:
countLongs :: [String] -> Int
countLongs [] = 0
countLongs (x:xs) = if length(x)>5
    then 1 + countLongs xs
    else 0 + countLongs xs

--8.Defina uma função recursiva onlyLongs :: [String] -> [String] que receba uma lista de palavras e retorne outra lista somente com as palavras que tenham mais de 5 caracteres. 
onlyLongs :: [String] -> [String]
onlyLongs [] = []
onlyLongs (x:xs) = if length(x)>5
    then x:onlyLongs xs
    else onlyLongs xs