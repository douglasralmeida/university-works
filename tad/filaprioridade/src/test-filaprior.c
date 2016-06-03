/*
**	TESTE DO TAD FILA COM PRIORIDADE
**	DOUGLAS RODRIGUES DE ALMEIDA
**
**	Teste do TAD Fila
**	
**/

#include <stdio.h>
#include <stdlib.h>
#include "filaprior.h"

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
	TFilaPrioridade* Fila;
	
	FuncaoDestruir = &DestruirInt;
	FuncaoImprimir = &ImprimirInt;
	
	printf("TESTE FILA COM PRIORIDADE\n");
	printf("=========================\n");
	
	printf("Criando fila com prioridade...");
	Fila = TFilaPrioridade_Criar(FuncaoDestruir, FuncaoImprimir);
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
	TFila_Imprimir(Fila);
	printf("OK.\n");
	
	printf("Limpando fila...");
	TFila_Limpar(Fila);
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
	TFila_Imprimir(Fila);
	printf("OK.\n");

	printf("Desenfileirando fila...");
	dado = (int*)TFila_Desenfileirar(Fila);
	printf("Item %d. ", *dado);
	free(dado);
	dado = (int*)TFila_Desenfileirar(Fila);
	printf("Item %d. ", *dado);
	free(dado);
	printf("OK.\n");

	printf("Exibindo fila...");
	TFila_Imprimir(Fila);
	printf("OK.\n");	

	printf("Destruindo fila...");
	TFila_Destruir(&Fila);
	printf("OK.\n");
	
	exit(EXIT_SUCCESS);
}
