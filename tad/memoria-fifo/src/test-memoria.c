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

bool IntComparar(void* Int1, void* Int2)
{
	return (*(int*)Int1 < *(int*)Int2);
}

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
	Memoria->FuncaoComparar = &IntComparar;

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

	printf("Preenchendo memória...");
	for (i = 0; i < Memoria->Capacidade; i++)
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

	printf("Preenchendo na fila ordenadamente...");
	for (i = Memoria->Capacidade; i > 0; i--)
	{
		dado = (int*)malloc(sizeof(int));
		*dado = i;
		TMemoria_EscreverNaOrdem(Memoria, dado);
	}
	printf("OK.\n");

	printf("Removendo da memória ordenada três elementos...");
	dado = (int*)TMemoria_LerPrimeiro(Memoria);
	printf("%d ", *dado);
	free(dado);
	dado = (int*)TMemoria_LerPrimeiro(Memoria);
	printf("%d ", *dado);
	free(dado);
	dado = (int*)TMemoria_LerPrimeiro(Memoria);
	printf("%d ", *dado);
	free(dado);
	printf("OK.\n");	
	
	printf("Inserindo ordenadamente na memória mais elementos...");
	for (i = 53; i > 50; i--)
	{
		dado = (int*)malloc(sizeof(int));
		*dado = i;
		TMemoria_EscreverNaOrdem(Memoria, dado);
	}
	printf("OK.\n");

	printf("Esvaziando memoria ordenada...");
	for (i = 0; i < Memoria->Capacidade; i++)
	{
		dado = (int*)TMemoria_LerPrimeiro(Memoria);
		printf("%d ", *dado);
		free(dado);
	}
	printf("OK.\n");

	printf("Teste (1)...");
	TMemoria_Destruir(&Memoria);
	Memoria = TMemoria_Criar(3);
	if (Memoria != NULL)
		printf("OK.\n");
	else
		exit(EXIT_FAILURE);
	Memoria->FuncaoComparar = &IntComparar;
	dado = (int*)malloc(sizeof(int));
	*dado = 25;
	TMemoria_EscreverNaOrdem(Memoria, dado);
	dado = (int*)malloc(sizeof(int));
	*dado = 35;
	TMemoria_EscreverNaOrdem(Memoria, dado);
	dado = (int*)malloc(sizeof(int));
	*dado = 20;
	TMemoria_EscreverNaOrdem(Memoria, dado);
	dado = (int*)TMemoria_LerPrimeiro(Memoria);
	printf("%d ", *dado);
	free(dado);
	dado = (int*)malloc(sizeof(int));
	*dado = 23;
	TMemoria_EscreverNaOrdem(Memoria, dado);
	dado = (int*)TMemoria_LerPrimeiro(Memoria);
	printf("%d ", *dado);
	free(dado);
	dado = (int*)TMemoria_LerPrimeiro(Memoria);
	printf("%d ", *dado);
	free(dado);
	dado = (int*)malloc(sizeof(int));
	*dado = 38;
	TMemoria_EscreverNaOrdem(Memoria, dado);
	dado = (int*)malloc(sizeof(int));
	*dado = 30;
	TMemoria_EscreverNaOrdem(Memoria, dado);
	dado = (int*)TMemoria_LerPrimeiro(Memoria);
	printf("%d ", *dado);
	free(dado);
	dado = (int*)TMemoria_LerPrimeiro(Memoria);
	printf("%d ", *dado);
	free(dado);
	dado = (int*)TMemoria_LerPrimeiro(Memoria);
	printf("%d ", *dado);
	free(dado);
	printf("OK.\n");

	printf("Destruindo memoria...");
	TMemoria_Destruir(&Memoria);
	printf("OK.\n");
	
	exit(EXIT_SUCCESS);
}
