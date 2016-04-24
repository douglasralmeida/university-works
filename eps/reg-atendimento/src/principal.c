#include <stdio.h>
#include <stdlib.h>
#include "arquivo.h"

#define CMD_CLIENTECHEGADA 1
#define CMD_ATENDIMENTOINICIO 2
#define CMD_ATENDIMENTOFIM 3
#define CMD_CLIENTEDESISTE 4
#define CMD_RELATORIO 5
#define CMD_SAIR 6

int main(int argc, char *argv[])
{
	int ArquivoEntrada;
	
	if (argc > 2)
	{
		ArquivoEntrada = ArquivoAbrir(argv[1]);
		if (ArquivoEntrada > -1)
		{
			ArquivoAnalisar(ArquivoEntrada);
			ArquivoFechar(ArquivoEntrada);
		}
		else
		{
			printf("Erro ao abrir arquivo de entrada.\n");
		}
	}
	exit(EXIT_SUCCESS);
}
