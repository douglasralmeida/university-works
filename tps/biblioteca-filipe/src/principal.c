/*
**	BIBLIOTECA DO FILIPE
**	DOUGLAS RODRIGUES DE ALMEIDA
**
**	Aplicativo principal
*/

#include <stdio.h>

int main()
{
	char nomelivro[51];
	int livrodisponivel;
	unsigned long numlivros, numlivrosmemoria, numestantes, numlivrosporestante, numconsultas;
	unsigned long i;
		
	scanf("%lu, %lu, %lu, %lu, %lu", &numlivros, &numlivrosmemoria, &numestantes, &numlivrosporestante, &numconsultas);
	for (i = 0; i < numlivros; i++
	{
		scanf("%50s, %d", nomelivro, &livrodisponivel);
	}
	for (i = 0; i < numconsultas; i++)
	{
		scanf("%50s", nomelivro);
	}

	exit(EXIT_SUCCESS);
}
