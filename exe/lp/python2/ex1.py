## Escreva em Python programa que leia varios caracteres, que devem ser
## digitos de '0' a '9) e imprima o maior valor inteiro que se pode formar 
## com esses digitos, de modo que: 
##  se um caracterea lido nao for um digito uma mensagem
## (contendo o caractere digitado que nao é um digito) deve ser emitida, 
## e um novo caractere deve ser lido; 
## a leitura deve terminar quando um caractere '-' for lido.
## O programa deve  e usar funcao charPraInt que recebe um caractere,
## retorna o inteiro correspondente, se o caractere for um digito entre 
## '0' e '9, senao causa uma excecao, que contem o caractere digitado que 
## nao e digito.
lista = list()

def charPraInt(char):
    if char.isdigit():
        return int(char)
    else:
        raise Exception(char)

def getChar():
    res = input('Digite um algarismo: ')
    return res

def printMaiorNumero(listnum):
    listnum.sort(reverse=True)
    print('Maior número: ', end='', flush=True)
    for i in listnum:
        print(i, end='', flush=True)

def main():
    res = getChar()
    while (res != '-'):
        try:
            numero = charPraInt(res)
            lista.append(numero)
        except Exception as ex:
            print('O caractere {0} não é um inteiro.'.format(ex.args[0]))
        res = getChar()
    printMaiorNumero(lista)
    
main()