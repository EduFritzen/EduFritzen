--1.O Índice de Massa Corporal (IMC) é dado pelo peso dividido pela altura ao quadrado. Dependendo do valor resultante, um indivído adulto pode ser considerado abaixo do peso ideal (menor ou igual a 18.5), acima do peso ideal (maior ou igual a 30) ou dentro do peso normal (faixa intermediária). Sabendo disso, crie uma função bmi :: Float -> Float -> String que receba peso e altura e retorne um destes valores: "ABAIXO", "NORMAL" ou "ACIMA", dependendo do IMC calculado. Use let..in para declarar o cálculo do valor do IMC e aproveitá-lo em cada condição testada.
bmi :: Float -> Float -> String
bmi p h =
    let imc = p/(h*h)
     in if imc<=18.5 then "ABAIXO" else if imc>=30 then  "ACIMA" else "NORMAL"


--2.Resolva o exercício anterior usando where. A assinatura da nova função será bmi' :: Float -> Float -> String.
bmi' :: Float -> Float -> String
bmi' p h
  | imc <= 18.5 = "ABAIXO"
  | imc >= 30 = "ACIMA"
  | otherwise = "NORMAL"
  where imc = p / (h * h)

--3.O exemplo de validação de CPF mostrado nos slides tem 3 funções: uma que faz I/O e outras 2 que tratam do cálculo do dígito verificador. A função cpfValid usa let..in e a função cpfDV usa where. Reescreva estas 2 funções, trocando let..in por where e vice-versa.
cpfValid :: [Int] -> Bool
cpfValid cpf = dv1 == cpf !! 9 && dv2 == cpf !! 10 
  where digits = take 9 cpf
        dv1 = cpfDV digits [10,9..]
        dv2 = cpfDV (digits ++ [dv1]) [11,10..]


cpfDV :: [Int] -> [Int] -> Int
cpfDV digits mults =
  let expr = (sum $ zipWith (*) digits mults) `mod` 11
   in if expr < 2 then 0 else 11-expr


--4.Crie uma função andTable :: [(Bool, Bool, Bool)] que gere uma tabela verdade para o operador AND lógico, com o seguinte resultado:
andTable :: [(Bool, Bool, Bool)]
andTable = [(x, y, x && y) | x <- [True, False], y <- [True, False]] 