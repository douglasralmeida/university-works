-- TP2 de LP
-- Douglas Rodrigues de Almeida

import Prelude hiding (map, dropWhile, break, words, concat)
import Data.Char
import Data.List hiding (map, dropWhile, break, words, concat)

-- Escreva, usando foldl ou foldr uma função que recebe uma lista de
-- cadeias de caracteres (valores do tipo String) e retorna uma cadeia
-- de caracteres que contém os 3 primeiros caracteres de cada cadeia.
-- ex: Por exemplo, ao receber ["Abcde", "1Abcde", "12Abcde", "123Abcde"]
--     deve retornar "Abc1Ab12A123".


-- Escreva, usando foldr ou foldl, uma função que recebe uma lista de valores
-- do tipo Pessoa, definido a seguir, e retorna a soma das idades (valores do
-- campo idade) de todos os elementos da lista.
--  data Pessoa = Pessoa {nome::Nome, idade::Idade, id::RG}
--  type Nome = String
--  type Idade = Integer 
--  type RG = String


-- Escreva, usando foldr ou foldl, uma função que recebe uma lista não vazia de
-- valores de tipo Pessoa, da definição acima, e retorna o nome da pessoa mais
-- nova da lista.


-- A função remdups remove elementos iguais adjacentes de uma lista, conservando
-- só um dos elementos. 
-- Por exemplo, remdups [1,2,2,3,3,3,1,1] = [1,2,3,1].
-- Defina remdups usando foldr ou foldl.


-- TESTES

-- Teste ex1
lista1 = ["Abcde", "1Abcde", "12Abcde", "123Abcde"]

main = do
  print("ex1")