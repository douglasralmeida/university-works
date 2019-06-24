-- dobraIncPosDecNeg usa map e retorna uma lista em que cada elemento (a,b) da lista é igual a:
--    (2*a,b+1) se a+b for positivo
--    (a,b-1) se a+b for negativo
--    (0,0) se a+b for igual a zero
dobraIncPosDecNeg :: [(Integer,Integer)] -> [(Integer,Integer)]
dobraIncPosDecNeg = map f
                       where f (a,b)
                              | a+b > 0 = (2*a, b+1)
                              | a+b < 0 = (a, b-1)
                              | otherwise  = (0,0)

-- tiraSomaZero usa filter para retornar a lista em que cada elemento (a,b) da lista é
-- descartado se a+b for igual a zero
tiraSomaZero :: [(Integer,Integer)] -> [(Integer,Integer)]
tiraSomaZero xs = filter f xs
                      where f (a,b) = a+b /= 0

-- comb12 usa foldr e é uma combinação das funcoes tiraSomaZero e dobraIncPosDecNeg
comb12 :: [(Integer,Integer)] -> [(Integer,Integer)]
comb12 =  dobraIncPosDecNeg . tiraSomaZero

comb12Puro :: [(Integer,Integer)] -> [(Integer,Integer)]
comb12Puro = foldr f []
  where f (a,b) x
          | a+b > 0 = (2*a, b+1):x
          | a+b < 0 = (a, b-1):x
          | otherwise  = x

lista1 = [(2,1),(0,1),(2,-2),(-1,0)]
lista2 = dobraIncPosDecNeg lista1
lista3 = tiraSomaZero lista1
lista4 = comb12 lista1

main = do
    print("dobraIncPosDecNeg")
    print(lista2)
    print("tiraSomaZero")
    print(lista3)
    print("comb12")
    print(lista4)
    print("combPuro")
    print(lista4)