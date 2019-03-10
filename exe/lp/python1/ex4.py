## Escreva em Python programa que leia varios caracteres, que devem ser
## digitos de '0' a '9) e imprima o maior valor inteiro que se pode formar 
## com esses digitos, de modo que: 
##  se um caracterea lido nao for um digito uma mensagem
## (contendo o caractere digitado que nao é um digito) deve ser emitida, 
## e um novo caractere deve ser lido; 
## a leitura deve terminar quando um caractere '-' for lido.
## O programa deve de
nir e usar funcao charPraInt que recebe um caractere, 
## retorna o inteiro correspondente, se o caractere for um digito entre 
## '0' e '9, senao causa uma excecao, que contem o caractere digitado que 
## nao e digito.

import itertools

def yieldfunc(texto):
    for lin in texto:
        yield lin

def imprimir(arq):
    for lin in arq:
        print(lin)
    print('\n')
    
def processar(n, tam, texto):
    i = 1
    j = 1
    while (i < tam):
        li = (i-1) * n + 1
        lf = i*n
        while (j < li):
            yieldfunc(texto)
            j += 1
        j = li+1
        arq = yieldfunc(texto)
        while (j <= lf):
            itertools.chain(arq, yieldfunc(texto))
            j += 1
        imprimir(arq)
        i += 1
        
def tamtexto(texto):
    return sum(1 for _ in texto)

def main(n, arq):
    texto = open(arq, 'rt')
    totallinhas = tamtexto(texto)
    texto.seek(0)
    processar(n, totallinhas, texto)

main(5, 'z')


#i 	li 		   lf
#1	0+1		   n                0 1
#2	1*n+1		2*n              3 4
#3	2*n+1		3*n              7 9
#...........................
#n	(n-1)*n+1	n*n