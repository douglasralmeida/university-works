## Escreva uma função que receba um inteiro n e uma lista de nomes de
## arquivos como argumentos e imprima todas as linhas contidas nos
## arquivos com tamanho maior que n caracteres.

def obtemlinhas(arqs):
    for arq in arqs:
        for linha in open(arq, 'rt'):
            yield linha

def imprimir_maiorn(n, linhas):
    for x in (lin.strip() for lin in linhas if len(lin.strip()) > n):
        print(x)

def exe1(n, arqs):
    linhas = obtemlinhas(arqs)
    imprimir_maiorn(n, linhas)

## Escreva um programa que receba uma lista de nomes de arquivos como
## argumentos e imprima
##   i) para cada arquivo, seu nome e o numero de linhas contidas no arquivo,
##  ii) o numero total de linhas contidas nos arquivos.

def contarlinhas(arqs):
    for arq in arqs:
        i = 0
        for linha in open(arq, 'rt'):
            i += 1
        yield arq, i

def exe2(arqs):
    lintotal = 0
    gen = contarlinhas(arqs)
    for arq, lin in gen:
        print("{0} {1}".format(arq, lin))
        lintotal += lin
    print(lintotal)

## Escreva uma funcao enumerate_ que se comporte como enumerate.
## A funcao enumerate recebe um iterador it e retorna um iterador 
## sobre pares (i,v), onde i e um indice e v um valor, do iterador it.

def enumerate_(it):
    i = 0
    while i < len(it):
        yield (i, it[i])
        i += 1

def exe3(arg):
    lista = list(enumerate_(arg))
    print(lista)

    for i, c in enumerate_(arg):
        print(i, c)

# Testes
listaarquivos = ['a', 'b', 'c']

print("Exercicio 1:")
exe1(2, listaarquivos)

print("\nExercicio 2:")
exe2(listaarquivos)

print("\nExercicio 3:")
exe3(listaarquivos)