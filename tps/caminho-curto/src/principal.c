/*
**	TP1
**	DOUGLAS RODRIGUES DE ALMEIDA
**
**	Aplicativo principal
*/

#include <stdio.h>
#include <stdlib.h>
#include "servidor.h"
#include "hora.h"

int main(int argc, char *argv[])
{
	TProcessador* Processador;
	
	if (argc > 1)
	{
		Processador = TProcessador_Criar();
		if (Processador == NULL)
			exit(EXIT_FAILURE);
		if (TProcessador_CarregarDados(Processador, argv[1]))
			TProcessador_AnalisarDados(Processador);
		TProcessador_Destruir(&Processador);
	}
	else
	{
		printf("Erro ao procesar argumentos.\n");
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}