-- Lista 2 de LP
-- Douglas Rodrigues de Almeida

import Prelude hiding (id)
import Data.Char

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

-- Escreva, usando foldl ou foldr, uma função que recebe uma lista de cadeias
-- de caracteres (valores do tipo String) e retorna uma cadeia de caracteres
-- que contém os 3 primeiros caracteres de cada cadeia removidos se não forem
-- letras, ou com as letras em caixa alta se forem letras, e com os demais
-- caracteres depois dos 3 primeiros sem alteração.
-- ex: Por exemplo, ao receber ["Abcde", "1Abcde", "12Abcde", "123Abcde"] deve retornar "ABCdeABcdeAbcdeAbcde"
tresPrimeirosMaiusculas :: [String] -> String
tresPrimeirosMaiusculas xs = foldr foldTresMaius [] xs
  where foldTresMaius e ls = processar(e) ++ ls
        processar (c1:c2:c3:cs) = alterar(c1).alterar(c2).alterar(c3) $ cs
        alterar c cs
          | isAlpha c = toUpper c:cs
          | otherwise = cs

-- Explique porque foldr f x pode não percorrer toda a lista x, ao passo que toda a lista x é sempre percorrida, no caso de foldl.
--  R: No caso de foldr, o resultado da avaliação de f pode ser constante. Seja e1, e2...en os elementos da lista, em alguns casos,
--  não é necessário avaliar e2..en para saber o resultado de f e1 e2.
--  No caso de foldl é necessário avaliar a lista inteira pois a avaliação é sempre feita a partir da função mais externa, ou seja,
--  o resultado da avaliação de f é O(n).

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

-- Teste ex2 e ex3
pessoa1 = Pessoa {nome="Maria", idade=50, id="1235"}
pessoa2 = Pessoa {nome="Joao", idade=24, id="465415"}
pessoa3 = Pessoa {nome="Jose", idade=25, id="9551"}
listaPessoa = pessoa1:pessoa2:pessoa3:[]
somaIdade = somaIdadePessoa listaPessoa
maisNova = pessoaMaisNova listaPessoa

-- Teste ex4
lista4 = ["Abcde", "1Abcde", "12Abcde", "123Abcde"]
lista4res = tresPrimeirosMaiusculas lista4
-- deve retornar "ABCdeABcdeAbcdeAbcde"

-- Teste ex6
lista6 = [1,2,2,3,3,3,1,1]
lista6res = remdups lista6

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
  print(lista4)
  print(lista4res)
  print("ex6")
  print(lista6)
  print(lista6res)