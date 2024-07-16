module Lam where
import ParserTodo

-- Definição dos termos no cálculo lambda sem nomes (Nameless Lambda)
data NamelessLambdaExpr = Nvar Int      -- Representa uma variável com um índice de Bruijn
           | NAbs NamelessLambdaExpr    -- Representa uma abstração (lambda)
           | NApp NamelessLambdaExpr NamelessLambdaExpr -- Representa uma aplicação de termos
           deriving(Show,Eq)

type Ctx = [(Char,Int)] -- Context de nomes 

-- Context inicial de nomes (mapeamento de variáveis para seus índices)
names_context1 :: Ctx
names_context1 = [('x',4),('y',3),('z',2),('a',1),('b',0)]

-- Adiciona uma variável ao context, inicializando com índice 0
addVariableToContext :: Char -> Ctx -> Ctx
addVariableToContext var context = (var, 0) : [(c, n + 1) | (c, n) <- context]

-- Encontra o índice de Bruijn associado a uma variável no context
findIndexInContext :: Char -> Ctx -> Int
findIndexInContext var context = head [n | (c, n) <- context, c == var]

-- Converte termos com nomes para a representação nameless usando índices de Bruijn
convertToNameless :: Term -> NamelessLambdaExpr
convertToNameless x = removeNames x names_context1 0

removeNames :: Term -> Ctx -> Int -> NamelessLambdaExpr
removeNames (Var v) ctx c = Nvar (findIndexInContext v ctx) -- Converte uma variável com nome para um índice de Bruijn
removeNames (Abs p b) ctx c = NAbs (removeNames b (addVariableToContext p ctx) (c + 1)) -- Converte uma abstração para a representação nameless recursivamente
removeNames (App t1 t2) ctx c = NApp (removeNames t1 ctx c) (removeNames t2 ctx c) -- Converte aplicação de termos para a representação nameless

-- Realiza o deslocamento dos índices de Bruijn em uma substituição
shift :: Int -> Int -> NamelessLambdaExpr -> NamelessLambdaExpr
shift d l (Nvar i) = if i < l then Nvar i else Nvar (i + d)
shift d l (NAbs b) = NAbs (shift d (l + 1) b)
shift d l (NApp t1 t2) = NApp (shift d l t1) (shift d l t2)

-- isVal modificado para avaliação nameless de termos
-- Verifica se um termo nameless é um valor ou uma aplicação
isVal :: NamelessLambdaExpr -> Bool
isVal (NApp _ _) = False
isVal _ = True

--Subs modificado para avaliação nameless de termos
-- Realiza a substituição de termos em termos nameless
subs :: Int -> NamelessLambdaExpr -> NamelessLambdaExpr -> NamelessLambdaExpr
subs j s (Nvar k) = if k == j then s else Nvar k
subs j s (NAbs b) = NAbs (subs (j+1) (shift 1 0 s) b)
subs j s (NApp t1 t2) = NApp (subs j s t1) (subs j s t2)

-- Implementa a redução beta em termos nameless
betaReduction :: NamelessLambdaExpr -> NamelessLambdaExpr -> NamelessLambdaExpr
betaReduction (NAbs b) arg = shift (-1) 0 (subs 0 (shift 1 0 arg) b)
betaReduction _ _ = error "Not an abstraction applied to an argument."

-- Realiza a avaliação recursiva de termos nameless
-- evaluation modificado para avaliação nameless de termos
evaluation :: NamelessLambdaExpr -> NamelessLambdaExpr
evaluation(NApp (NAbs p ) a) = let e = eval (NApp (NAbs p ) a)
                                              in if e == (NApp (NAbs p ) a)
                                                 then e
                                                 else evaluation (eval (NApp (NAbs p ) a))
evaluation(NApp t1 t2) = let e = eval (NApp t1 t2)
                                    in if e == (NApp t1 t2)
                                       then e
                                       else evaluation (eval(NApp t1 t2))
evaluation t = t

-- Realiza a avaliação de termos nameless no cálculo lambda
-- eval modificado para avaliação nameless de termos
eval :: NamelessLambdaExpr -> NamelessLambdaExpr
eval(NApp (NAbs p ) a) = if isVal a 
                                        then betaReduction a p
                                        else let a' = eval a
                                             in NApp (NAbs p) a'
eval(NApp t1 t2) = let t1' = eval t1 
                              in NApp t1' t2
eval t = t

-- Execução principal: integração com o parser, remoção de nomes, e avaliação de termos nameless
main :: IO()
main = getContents >>= print . evaluation . convertToNameless . parserlamb . lexer 