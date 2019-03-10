## Escreva um programa que receba uma lista de nomes de arquivos como
## argumentos e imprima
##   i) para cada arquivo, seu nome e o numero de linhas contidas no arquivo,
##  ii) o numero total de linhas contidas nos arquivos.

def yieldfunc(arq):
    for lin in open(arq, 'rt'):
        yield lin

def contar(lins):
    i = 0
    for lin in lins:
        i+=1
    return i

def main(arqs):
    linhastotal = 0
    for arq in arqs:
        lins = yieldfunc(arq)
        linhasarq = contar(lins)
        linhastotal += linhasarq
        print(arq + ' ' + str(linhasarq))
    print(linhastotal)

main(['a', 'b', 'c'])

#i 	li   		lf
#1	n+1   		n
#2	1*n+1		2*n
#3	2*n+1		3*n
#...........................
#n	(n-1)*n+1	n*n