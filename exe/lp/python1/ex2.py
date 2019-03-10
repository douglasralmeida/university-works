## Escreva um programa que receba uma lista de nomes de arquivos como
## argumentos e imprima o numero total de linhas contidas nos arquivos mas
## excluindo linhas em branco, isto e, linhas que contem apenas caracteres c
## para os quais c.isspace () e igual a True. Nota: o iterador de linhas de
## arquivos inclui o caractere 'nn' como parte (ultimo caractere) da linha (a
## condicao que testa a ocorrencia de apenas espacos em uma linha deve 
## considerar isso).

def yieldfunc(arqs):
    for arq in arqs:
        for lin in open(arq, 'rt'):
            yield lin

def filtro(linhas):
    return (lin for lin in linhas if not lin.isspace())

def imprimir(lins):
    i = 0
    for lin in lins:
        i+=1
    print(i)

def main(arqs):
    lins = yieldfunc(arqs)
    lins = filtro(lins)
    imprimir(lins)

main(['a', 'b', 'c'])