-- Lista 1 de LP
-- Douglas Rodrigues de Almeida

import Prelude hiding (map, dropWhile, break, words, concat)
import Data.Char
import Data.List hiding (map, dropWhile, break, words, concat)

-- Escreva funcao map:: (a->b) -> [a] -> [b] que recebe funcao f e lista x
-- e retorna a lista resultante de aplicar f a cada elemento de x.
map :: (a->b) -> [a] -> [b]
map f []     = []
map f (x:xs) = f x : map f xs

-- Escreva funcao mudaPraMinusc :: String -> String que transforma toda letra
-- maiuscula no argumento em letra minuscula, conservando sem mudanca os demais
-- caracteres.
-- Use map e toLower (definida em Data.Char).
mudaPraMinusc :: String -> String
mudaPraMinusc s = map toLower s

-- Escreva a funcao dropWhile :: (a->Bool) -> [a] -> [a], que recebe um predicado 
-- (funcao que retorna valor de tipo Bool ) p e uma lista x e remove cada elemento
-- a de x para o qual p a é verdadeiro, a partir do primeiro, até encontrar um valor
-- b para o qual p b é falso.
-- Exemplos:
-- dropWhile(<0) [-1,2,-3,4] retorna [2,-3,4].
-- dropWhile(>0) [-1,2,-3,4] retorna [-1,2,-3,4].
dropWhile :: (a->Bool) -> [a] -> [a]
dropWhile p [] = []
dropWhile p all@(x:xs)
  | p x       = dropWhile p xs
  | otherwise = all
    
-- Escreva a funcão break :: (a -> Bool) -> [a] -> ([a],[a]), que recebe um predicado p
-- e uma lista x e particiona a lista x em duas sublistas x1,x2, sendo x1 a lista
-- contendo os elementos de x até que o predicado seja verdadeiro e x2 o restante dos
-- elementos de x, do elemento para o qual o predicado retorna verdadeiro seguido dos
-- elementos restantes de x.
-- Exemplos:
-- break(<0) [-1,2,-3,4] retorna ([],[-1,2,-3,4]).
-- break(>0) [-1,2,-3,4] retorna ([-1],[2,-3,4]).
break :: (a->Bool) -> [a] -> ([a],[a])
break p [] = ([], [])
break p all@(x:xs)
  | not (p x)  =  (x:ys,zs) 
  | otherwise  =  ([],all)
    where (ys,zs) = break p xs

-- Considere a função splitWith :: (a->Bool) -> [a] -> [[a]], definida a seguir:
--  splitWith p = splitWith' p . dropWhile p
--  splitWith' p [] = []
--  splitWith' p x = x1 : splitWith p x2
--    where (x1 ,x2) = break p x
-- Defina a função words :: String -> [String], que recebe uma cadeia de caracteres s
-- e retorna a lista de palavras em s. Uma palavra é separada de outra por um ou mais
-- caracteres c para os quais isSpace c retorna verdadeiro (True).
-- A função isSpace é definida em Data.Char.
splitWith :: (a->Bool) -> [a] -> [[a]]
splitWith p = splitWith' p . dropWhile p
splitWith' p [] = []
splitWith' p x  = x1 : splitWith p x2
  where (x1 ,x2) = break p x
  
words :: String -> [String]
words s = splitWith isSpace s

-- Escreva função contaOcs :: [String] -> [(Int,String)] que recebe uma lista ordenada
-- de cadeias de caracteres xs e retorna uma lista de pares (n; x) onde n é o número de
-- vezes que x ocorre na lista ordenada (n > 0).
-- Exemplo:
-- contaOcs["a", "a", "b", "c", "c", "c", "d"] retorna:
--   [(2,"a"), (1,"b"), (3,"c"), (1,"d")]
contaOcs :: [String] -> [(Int,String)]
contaOcs cs = foldr foldContaOcs [] cs
  where foldContaOcs s [] = (1, s):[]
        foldContaOcs s ((n, ch):cs) = if ch == s then (n + 1, s) : cs
                                      else (1, s): (n, ch): cs

-- Escreva função concat :: [[a]] -> [a], que recebe uma lista de listas
-- xi (i = 1; : : : ; n) e retorna o resultado de concatenar os elementos em
-- todas as listas xi.
-- Exemplo: concat[[1,2],[3,4,5],[6]] retorna [1,2,3,4,5,6].
concat :: [[a]] -> [a]
concat xs = foldr (++) [] xs

-- Escreva função palavrasMaisComuns :: Int -> String -> String que recebe
-- um inteiro n e uma cadeia de caracteres texto e retorne a lista das
-- n palavras mais comuns em texto; para cada uma das n palavras mais
-- comuns deve ser retornda uma linha contendo a palavra e o número de
-- ocorrências dessa palavra em texto.
-- Use: mudaPraMinusc, words, sort, contaOcs, sortBy, take, map, concat:
-- encadeie chamadas dessas funções com a função (.) de composição de
-- funções.
palavrasMaisComuns :: Int -> String -> String
palavrasMaisComuns 0 s = []
palavrasMaisComuns n "" = []
palavrasMaisComuns n s = concat(map transform (take n (sortBy compareFunc (contaOcs.sort.words.mudaPraMinusc $ s))))
                                where compareFunc a b = b `compare` a
                                      transform (i, s) = s ++ " " ++ show(i) ++ "\n"

-- TESTES

-- Teste ex1
dobrar x = 2*x
lista1 = [1,2,3,4]
listadobro = map dobrar lista1

-- Teste ex2
maius = "Casa123* CASA !"
minus = map toLower maius

-- Teste ex3
lista3 = [2, 4, 5, 7, 8, 9]
listadroped = dropWhile even lista3

-- Teste ex4
lista4 = "ola mundo"
listadividida = break ('m'==) lista4 

-- Teste ex5
lista5 = "minha terra tem palmeiras"
listapalavras = words lista5

-- Teste ex6
lista6 = ["a", "a", "b", "c", "c", "c", "d"]
listaacumulada = contaOcs lista6

-- Teste ex7
lista7 = [[1,2],[3,4,5],[6]]
listaconcat = concat lista7

-- Teste ex8
lista8 = "casa estava casa casada casao estava casa esta casa cada casa casa estava"
lista8res = palavrasMaisComuns 3 lista8

main = do
  print("ex1")
  print(lista1)
  print(listadobro)
  print("ex2")
  print(maius)
  print(minus)
  print("ex3")
  print(lista3)
  print(listadroped)
  print("ex4")
  print(lista4)
  print(listadividida)
  print("ex5")
  print(lista5)
  print(listapalavras)
  print("ex6")
  print(lista6)
  print(listaacumulada)
  print("ex7")
  print(lista7)
  print(listaconcat)
  print("ex8")
  print(lista8)
  putStr(lista8res)