## Lista 5 de LP - Parte 1
## Douglas Rodrigues de Almeida


from math import pi
from sys import exit

class Forma:
        def area(self):
                print("area nao implementada")

        def perimetro(self):
                perint("perimetro nao iplementado")

class Quadrado(Forma):
        def __init__(self):
                self.lado = float(input("Digite valor (para lado do quadrado): "))

        def area(self):
                return self.lado * self.lado

        def nome(self):
                return "quadrado"

        def perimetro(self):
                return self.lado * 4

class Circulo(Forma):
        def __init__(self):
                self.raio = float(input("Digite valor (para raio do circulo): "))
        
        def area(self):
                return pi * self.raio * self.raio
        
        def nome(self):
                return "circulo"

        def perimetro(self):
                return 2 * pi * self.raio

class Triangulo(Forma):
        def __init__(self):
                self.lado1 = float(input("Digite valor (para lado 1 do triangulo): "))
                self.lado2 = float(input("Digite valor (para lado 2 do triangulo): "))
                self.lado3 = float(input("Digite valor (para lado 3 do triangulo): "))

        def area(self):
                s = self.perimetro() / 2.0
                return s * (s - self.lado1) * (s - self.lado2) * (s - self.lado3)

        def nome(self):
                return "triangulo"

        def perimetro(self):
                return self.lado1 + self.lado2 + self.lado3

def main():
        f = input("Digite q para quadrado, c para circulo ou t para triangulo: ")
        while True:
                if f == 'q':
                        forma = Quadrado()
                        break
                elif f == 'c':
                        forma = Circulo()
                        break
                elif f == 't':
                        forma = Triangulo()
                        break
                else:
                        sys.exit()
        
        print("\tarea do {0} igual a {1}".format(forma.nome(), forma.area()))
        print("\tperimetro do {0} igual a {1}".format(forma.nome(), forma.perimetro()))

main()