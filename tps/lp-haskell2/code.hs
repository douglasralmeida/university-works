-- TP2 de LP
-- Douglas Rodrigues de Almeida

import Prelude hiding (id)

-- Escreva, usando foldl ou foldr uma função que recebe uma lista de
-- cadeias de caracteres (valores do tipo String) e retorna uma cadeia
-- de caracteres que contém os 3 primeiros caracteres de cada cadeia.
-- ex: Por exemplo, ao receber ["Abcde", "1Abcde", "12Abcde", "123Abcde"] deve retornar "Abc1Ab12A123".
tresPrimeiros :: [String] -> String
tresPrimeiros xs = foldr foldTres [] xs
  where foldTres s xs = (subStr s 0):(subStr s 1):(subStr s 2):xs
        subStr s n
          | length(s) > n  = s!!n

-- Escreva, usando foldr ou foldl, uma função que recebe uma lista de valores
-- do tipo Pessoa, definido a seguir, e retorna a soma das idades (valores do
-- campo idade) de todos os elementos da lista.
--  data Pessoa = Pessoa {nome::Nome, idade::Idade, id::RG}
--  type Nome = String
--  type Idade = Integer 
--  type RG = String
type Nome = String
type Idade = Integer
type RG = String
data Pessoa = Pessoa {nome::Nome, idade::Idade, id::RG} deriving (Show) 
somaIdadePessoa :: [Pessoa] -> Idade
somaIdadePessoa ps = foldr (\p soma -> idade p + soma) 0 ps

-- Escreva, usando foldr ou foldl, uma função que recebe uma lista não vazia de
-- valores de tipo Pessoa, da definição acima, e retorna o nome da pessoa mais
-- nova da lista.
pessoaMaisNova :: [Pessoa] -> String
pessoaMaisNova ps = fst (procurar ps)
  where procurar (fp:ps) = foldr (\p (n, m) -> if idade p < m then (nome p, idade p) else (n, m)) (nome fp, idade fp) ps

-- A função remdups remove elementos iguais adjacentes de uma lista, conservando
-- só um dos elementos. 
-- Por exemplo, remdups [1,2,2,3,3,3,1,1] = [1,2,3,1].
-- Defina remdups usando foldr ou foldl.
remdups :: [Integer] -> [Integer]
remdups is = foldr folddups [] is
  where folddups i []     = i:[]
        folddups i is
          | i == last(is) = is
          | otherwise = is ++ [i]

-- TESTES

-- Teste ex1
lista1 = ["Abcde", "1Abcde", "12Abcde", "123Abcde"]
lista1res = tresPrimeiros lista1

-- Teste ex2
pessoa1 = Pessoa {nome="Maria", idade=50, id="1235"}
pessoa2 = Pessoa {nome="Joao", idade=24, id="465415"}
pessoa3 = Pessoa {nome="Jose", idade=25, id="9551"}
listaPessoa = pessoa1:pessoa2:pessoa3:[]
somaIdade = somaIdadePessoa listaPessoa
maisNova = pessoaMaisNova listaPessoa

-- Teste ex3
lista3 = [1,2,2,3,3,3,1,1]
lista3r = remdups lista3

main = do
  print("ex1")
  print(lista1)
  print(lista1res)
  print("ex2")
  print(listaPessoa)
  print(somaIdade)
  print("ex3")
  print(maisNova)
  print("ex4")
  print(lista3)
  print(lista3r)