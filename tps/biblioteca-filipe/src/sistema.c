/*
**	BIBLIOTECA DO FILIPE
**	DOUGLAS RODRIGUES DE ALMEIDA
**
**	Implementação do sistema da biblioteca
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arquivo.h"
#include "sistema.h"

TSistema* TSistema_Criar(void)
{
	TSistema* NovoSistema;

	NovoSistema = malloc(sizeof(TSistema));
	if (!NovoSistema)
		return NULL;

	return NovoSistema;
}

void TSistema_Destruir(TSistema** PSistema)
{
	free(*PSistema);
	PSistema = NULL;
}

void TSistema_LerEntrada(void)
{
	char nomelivro[53];
	int tamstring;
	unsigned long numlivros, numlivrosnamemoria, numestantes, numlivrosporestante, numconsultas;
	unsigned long i;
	TArquivo* MassaDados;
	
	scanf("%lu %lu %lu %lu %lu", &numlivros, &numlivrosnamemoria, &numestantes, &numlivrosporestante, &numconsultas);
	getchar();
	getchar();

	MassaDados = TArquivo_Criar("livros_ordenados", amlTexto);
	for (i = 0; i < numlivros; i++)
	{
		fgets(nomelivro, 52, stdin);
		tamstring = strlen(nomelivro);
		TArquivo_ApensarNoFinal(MassaDados, nomelivro, tamstring * sizeof(char));
	}
	TArquivo_Destruir(&MassaDados);

	for (i = 0; i < numconsultas; i++)
	{
		scanf("%50s", nomelivro);
		getchar();
	}
}
