## Defina classe Data, que represente uma data do calendario | i.e. 
## cujos objetos tem variaveis que representam dia, mes e ano |, de modo
## que a inicializacao de objetos da classe cause uma excecao se o dia, mes
## e ano passados como argumentos para a inicializacao de variaveis do 
## objeto nao representarem uma data valida.
## Considere anos bissextos. O tratamento da excecao pode apenas emitir 
## mensagem de data invalida, apos armazenamento dos valores passados 
## para inicializaao do objeto.

def eAnoBissexto(ano):
    return (ano % 4 == 0 and (ano % 400 == 0 or ano % 100 != 0))

class Date:
    def __init__(self, dia, mes, ano):
        self.dia = dia
        self.mes = mes
        self.ano = ano
        self.bissexto = eAnoBissexto(ano)
        self.checar()
        
    def __str__(self):
        return str(self.dia) + '/' + str(self.mes) + '/' + str(self.ano)
    
    def checar(self):
        if self.dia < 1 or self.dia > 31:
            raise Exception('Data inválida')
        if self.mes < 1 or self.mes > 12:
            raise Exception('Data inválida')
        if self.ano == 0:
            raise Exception('Data inválida')
        if self.mes in [4, 6, 9, 11]:
            if self.dia == 31:
                raise Exception('Data inválida')
        if self.mes == 2:
            if self.bissexto:
                if self.dia > 29:
                    raise Exception('Data inválida')
            else:
                if self.dia > 28:
                    raise Exception('Data inválida')

def main():
    data = Date(2, 4, 2018)
    print(data)
    
main()