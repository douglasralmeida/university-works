-- TP1 de LP
-- Douglas Rodrigues de Almeida

-- Escreva funcao map:: (a->b) -> [a] -> [b] que recebe funcao f e lista x
-- e retorna a lista resultante de aplicar f a cada elemento de x.
map :: (a->b) -> [a] -> [b]

-- Escreva funcao mudaPraMinusc:: String-> String que transforma toda letra
-- minuuscula no argumento em letra maiuscula, conservando sem mudanca os demais caracteres.
-- Use map e toLower (definida em Data.Char).
mudaPraMinusc :: String -> String

-- Escreva a funcao dropWhile::(a->Bool) -> [a] -> [a], que recebe um predicado 
-- (funcao que retorna valor de tipo Bool ) p e uma lista x e remove cada elemento
-- a de x para o qual p a é verdadeiro, a partir do primeiro, até encontrar um valor
-- b para o qual p b é falso.
-- Exemplos:
-- dropWhile(<0) [-1,2,-3,4] retorna [2,-3,4].
-- dropWhile(>0) [-1,2,-3,4] retorna [-1,2,-3,4].
dropWhile :: (a->Bool) -> [a] -> [a]

-- Escreva a funcão break::(a -> Bool) -> [a] -> ([a],[a]), que recebe um predicado p
-- e uma lista x e particiona a lista x em duas sublistas x1,x2, sendo x1 a lista
-- contendo os elementos de x até que o predicado seja verdadeiro e x2 o restante dos
-- elementos de x, do elemento para o qual o predicado retorna verdadeiro seguido dos
-- elementos restantes de x.
-- Exemplos:
-- break(<0) [-1,2,-3,4] retorna ([],[-1,2,-3,4]).
-- break(>0) [-1,2,-3,4] retorna ([-1],[2,-3,4]).
break :: (a -> Bool) -> [a] -> ([a],[a])

-- Considere a função splitWith :: (a->Bool) -> [a] -> [[a]], definida a seguir:
-- splitWith p = splitWith' p . dropWhile p
-- splitWith' p [] = []
-- splitWith' p x = x1 : splitWith p x2
--   where (x1 ,x2) = break p x
-- Defina a função words :: String -> [String], que recebe uma cadeia de caracteres s
-- e retorna a lista de palavras em s. Uma palavra é separada de outra por um ou mais
-- caracteres c para os quais isSpace c retorna verdadeiro (True).
-- A função isSpace e denida em Data.Char.
words :: String -> [String]

-- Escreva função contaOcs :: [String] -> [(Int,String)] que recebe uma lista ordenada
-- de cadeias de caracteres xs e retorna uma lista de pares (n; x) onde n é o número de
-- vezes que x ocorre na lista ordenada (n > 0).
-- Exemplo:
-- contaOcs["a", "a", "b", "c", "c", "c", "d"] retorna:
--   [(2,"a"), (1,"b"), (3,"c"), (1,"d")]
contaOcs :: [String] -> [(Int,String)]

-- Escreva função concat :: [[a]] -> [a], que recebe uma lista de listas
-- xi (i = 1; : : : ; n) e retorna o resultado de concatenar os elementos em
-- todas as listas xi.
-- Exemplo: concat[[1,2],[3,4,5],[6]] retorna [1,2,3,4,5,6].
concat :: [[a]] -> [a]

-- Escreva função palavrasMaisComuns :: Int -> String -> String que recebe
-- um inteito n e uma cadeia de caracteres texto e retorne a lista das
-- n palavras mais comuns em texto; para cada uma das n palavras mais
-- comuns deve ser retornda uma linha contendo a palavra e o número de
-- ocorrências dessa palavra em texto.
-- Use: mudaPraMinusc, words, sort, contaOcs, sortBy, take, map, concat:
-- encadeie chamadas dessas funções com a função (.) de composição de
-- funções.
palavrasMaisComuns :: Int -> String -> String