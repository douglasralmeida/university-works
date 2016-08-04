/*
**	TESTE DO TAD FILA
**	DOUGLAS RODRIGUES DE ALMEIDA
**
**	Teste do TAD Fila
**	
**/

#include <stdio.h>
#include <stdlib.h>
#include "fila.h"

void DestruirInt(void** PInt)
{
	if (PInt != NULL)
	{
		free(*PInt);
		PInt = NULL;
	}
}

void ImprimirInt(void* PInt)
{
	int* item;
	
	item = (int*)PInt;
	printf("%d ", *item);
}

int main(void)
{	
	int i;
	int* dado;
	TFuncaoDestruir FuncaoDestruir;
	TFuncaoImprimir FuncaoImprimir;
	TFila* Fila;
	
	FuncaoDestruir = &DestruirInt;
	FuncaoImprimir = &ImprimirInt;
	
	printf("TESTE FILA\n");
	printf("==========\n");
	
	printf("Criando fila...");
	Fila = TFila_Criar(11);
	if (Fila != NULL)
		printf("OK.\n");
	else
		exit(EXIT_FAILURE);

	printf("Preenchendo fila...");
	for (i = 0; i < 10; i++)
	{
		dado = (int*)malloc(sizeof(int));
		*dado = i;
		TFila_Enfileirar(Fila, dado);
	}
	printf("OK.\n");
	
	printf("Exibindo fila...");
	TFila_Imprimir(Fila, FuncaoImprimir);
	printf("OK.\n");

	printf("Tamanho da fila...");
	printf("%lu. ", (unsigned long)TFila_Tamanho(Fila));
	printf("OK.\n");
	
	printf("Limpando fila...");
	TFila_Limpar(Fila, FuncaoDestruir);
	printf("OK.\n");

	printf("Desenfileirando fila vazia...");
	TFila_Desenfileirar(Fila);

	printf("Tamanho da fila...");

	printf("%lu. ", TFila_Tamanho(Fila));
	printf("OK.\n");
	
	printf("Preenchendo fila...");
	for (i = 100; i < 110; i++)
	{
		dado = (int*)malloc(sizeof(int));
		*dado = i;
		TFila_Enfileirar(Fila, dado);
	}
	printf("OK.\n");

	printf("Exibindo fila...");
	TFila_Imprimir(Fila, FuncaoImprimir);
	printf("OK.\n");
	
	printf("Enfileirando fila cheia...");
	TFila_Enfileirar(Fila, dado);
	
	printf("Desenfileirando fila...");
	dado = (int*)TFila_Desenfileirar(Fila);
	printf("Item %d. ", *dado);
	free(dado);
	dado = (int*)TFila_Desenfileirar(Fila);
	printf("Item %d. ", *dado);
	free(dado);
	printf("OK.\n");

	printf("Tamanho da fila...");
	printf("%lu. ", (unsigned long)TFila_Tamanho(Fila));
	printf("OK.\n");

	printf("Exibindo fila...");
	TFila_Imprimir(Fila, FuncaoImprimir);
	printf("OK.\n");

	printf("Enfileirando item...");
	dado = (int*)malloc(sizeof(int));
	*dado = 150;
	TFila_Enfileirar(Fila, dado);
	printf("OK.\n");

	printf("Tamanho da fila...");
	printf("%lu. ", (unsigned long)TFila_Tamanho(Fila));
	printf("OK.\n");

	printf("Exibindo fila...");
	TFila_Imprimir(Fila, FuncaoImprimir);
	printf("OK.\n");

	printf("Destruindo fila...");
	TFila_Destruir(&Fila, FuncaoDestruir);
	printf("OK.\n");
	
	exit(EXIT_SUCCESS);
}
