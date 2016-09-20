/*
**	BIBLIOTECA DO FILIPE
**	DOUGLAS RODRIGUES DE ALMEIDA
**
**	Implementação do sistema da biblioteca
*/

#include <stdio.h>

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
	char nomelivro[51];
	int livrodisponivel;
	unsigned long numlivros, numlivrosnamemoria, numestantes, numlivrosporestante, numconsultas;
	unsigned long i;
		
	scanf("%lu, %lu, %lu, %lu, %lu", &numlivros, &numlivrosnamemoria, &numestantes, &numlivrosporestante, &numconsultas);
	for (i = 0; i < numlivros; i++
	{
		scanf("%50s, %d", nomelivro, &livrodisponivel);
	}
	for (i = 0; i < numconsultas; i++)
	{
		scanf("%50s", nomelivro);
	}
}
