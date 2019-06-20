-- Lista 5 de LP - Parte 3
-- Douglas Rodrigues de Almeida


type Lado = Float
type Raio = Float
data Forma = Quadrado Lado | Circulo Raio | Triangulo Lado Lado Lado

area (Quadrado lado) = lado * lado
area (Circulo raio) = pi * raio * raio
area (Triangulo lado1 lado2 lado3) =
                                let s = (lado1 + lado2 + lado3) / 2
                                in s * (s - lado1) * (s - lado2) * (s - lado3)
perimetro (Quadrado lado) = 4 * lado
perimetro (Circulo raio) = 2 * pi * raio
perimetro (Triangulo lado1 lado2 lado3) = lado1 + lado2 + lado3

quadrado:: IO Forma
quadrado = do
        putStrLn "Digite valor (para lado do quadrado): "
        s <- getLine
        return . Quadrado $ read s

circulo:: IO Forma
circulo = do
        putStrLn "Digite valor (para raio do circulo): "
        s <- getLine
        return . Circulo $ read s

triangulo:: IO Forma
triangulo = do
        putStrLn "Digite valor (para lado 1 do triangulo): "
        x <- getLine
        putStrLn "Digite valor (para lado 2 do triangulo): "
        y <- getLine
        putStrLn "Digite valor (para lado 3 do triangulo): "
        z <- getLine
        return (Triangulo (read x) (read y) (read z))

main = do
        putStrLn "Digite q para quadrado, c para circulo ou t para triangulo: "
        f <- getChar
        getLine
        let (nome, criarForma)
                | f == 'q' = ("quadrado", quadrado)
                | f == 'c' = ("circulo", circulo)
                | f == 't' = ("triangulo", triangulo)
        forma <- criarForma
        let areaForma = show $ area forma
        putStrLn ("area do " ++ nome ++ " igual a " ++ areaForma)
        let perimetroForma = show $ perimetro forma
        putStrLn ("perimetro do " ++ nome ++ " igual a " ++ perimetroForma)