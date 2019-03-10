## Escreva uma programa que receba um inteiro n e uma lista de nomes de 
## arquivos como argumentos e imprima todas as linhas contidas nos arquivos 
## com tamanho maior que n caracteres.

def yieldfunc(arqs):
    for arq in arqs:
        for lin in open(arq, 'rt'):
            yield lin

def filtro(n, linhas):
    return (lin for lin in linhas if len(lin.strip()) > n)

def imprimir(lins):
    for lin in lins:
        print(lin.strip())

def main(n, arqs):
    lins = yieldfunc(arqs)
    lins = filtro(n, lins)
    imprimir(lins)
    

main(2, ['a', 'b', 'c'])