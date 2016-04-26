#include <stdio.h>
#include <stdlib.h>
#include "atendimento.h"

int main(int argc, char *argv[])
{
	if (argc > 2)
	{
		AtendimentoProcessarEntrada(argv[1]);
	}
	else
	{
		printf("Erro ao abrir arquivo de entrada.\n");
	}
	exit(EXIT_SUCCESS);
}
