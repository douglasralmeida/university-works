/*
**	SERVIDOR DE IMPRESSSAO
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
	TServidor* Servidor;
	
	if (argc > 2)
	{
		Servidor = TServidor_Criar();
		if (Servidor != NULL)
		{
			if (TServidor_Preparar(Servidor, argv[1], argv[2]))
			{
				TServidor_Analisar(Servidor);
				TServidor_Finalizar(Servidor);				
			}
			TServidor_Destruir(&Servidor);
		}
		else
		{
			printf("Erro ao alocar memoria.\n");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		printf("Erro ao procesar argumentos.\n");
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}
