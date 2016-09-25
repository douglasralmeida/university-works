/*
**	TESTE DO TAD MEMORIA
**	DOUGLAS RODRIGUES DE ALMEIDA
**
**	Teste do TAD Memoria
**	
**/

#include <stdio.h>
#include <stdlib.h>
#include "memoria.h"

int main(void)
{	
	size_t i;
	int* dado;
	TMemoria* Memoria;
		
	printf("TESTE MEMORIA\n");
	printf("=============\n");

	printf("Criando memoria...");
	Memoria = TMemoria_Criar(10);
	if (Memoria != NULL)
		printf("OK.\n");
	else
		exit(EXIT_FAILURE);

	printf("Preenchendo memoria...");
	for (i = 0; i < Memoria->Capacidade; i++)
	{
		dado = (int*)malloc(sizeof(int));
		*dado = i;
		TMemoria_Escrever(Memoria, dado);
	}
	printf("OK.\n");
	
	printf("Esvaziando memoria (a partir do inicio)...");
	for (i = 0; i < Memoria->Capacidade; i++)
	{
		dado = (int*)TMemoria_LerPrimeiro(Memoria);
		printf("%d ", *dado);
		free(dado);
	}
	printf("OK.\n");

	printf("Preenchendo fila...");
	for (i = 0; i < 10; i++)
	{
		dado = (int*)malloc(sizeof(int));
		*dado = i;
		TMemoria_Escrever(Memoria, dado);
	}
	printf("OK.\n");

	printf("Esvaziando memoria (a partir do final)...");
	for (i = 0; i < Memoria->Capacidade; i++)
	{
		dado = (int*)TMemoria_LerUltimo(Memoria);
		printf("%d ", *dado);
		free(dado);
	}
	printf("OK.\n");

	printf("Preenchendo fila...");
	for (i = 0; i < 10; i++)
	{
		dado = (int*)malloc(sizeof(int));
		*dado = i;
		TMemoria_Escrever(Memoria, dado);
	}
	printf("OK.\n");

	printf("Esvaziando memoria (mesclado)...");
	for (i = 0; i < Memoria->Capacidade; i++)
	{
		if (i%2)
			dado = (int*)TMemoria_LerPrimeiro(Memoria);
		else
			dado = (int*)TMemoria_LerUltimo(Memoria);
		printf("%d ", *dado);
		free(dado);
	}
	printf("OK.\n");

	printf("Destruindo fila...");
	TMemoria_Destruir(&Memoria);
	printf("OK.\n");
	
	exit(EXIT_SUCCESS);
}
