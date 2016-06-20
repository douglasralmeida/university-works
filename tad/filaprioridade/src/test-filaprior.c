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

bool CompararInt(void* PInt1, void* PInt2)
{
	int* Int1;
	int* Int2;
	
	Int1 = (int*)PInt1;
	Int2 = (int*)PInt2;
	return ((*Int1) > (*Int2));
}

void DestruirInt(void** PInt)
{
	if (PInt != NULL)
	{
		free(*PInt);
		PInt = NULL;
	}
}

int main(void)
{	
	int i;
	int* dado;
	TFuncaoComparar FuncaoComparar;	
	TFuncaoDestruir FuncaoDestruir;
	TFilaPrioridade* Fila;
	
	FuncaoComparar = &CompararInt;
	FuncaoDestruir = &DestruirInt;
	
	printf("TESTE FILA COM PRIORIDADE\n");
	printf("=========================\n");
	
	printf("Criando fila com prioridade...");
	Fila = TFilaPrioridade_Criar(1024, FuncaoComparar, FuncaoDestruir);
	if (Fila != NULL)
		printf("OK.\n");
	else
		exit(EXIT_FAILURE);

	printf("Preenchendo fila...");
	for (i = 10; i > 0; i--)
	{
		dado = (int*)malloc(sizeof(int));
		*dado = i;
		printf("%d ",  *dado);
		TFilaPrioridade_Enfileirar(Fila, dado);
	}
	printf("OK.\n");
	
	printf("Desenfileirando fila...");
	while (Fila->Tamanho > 0)
	{
		dado = (int*)TFilaPrioridade_Desenfileirar(Fila);
		printf("Item %d. ", *dado);
		free(dado);
	}
	printf("OK.\n");

	printf("Preenchendo fila...");
	for (i = 100; i < 110; i++)
	{
		dado = (int*)malloc(sizeof(int));
		*dado = i;
		printf("%d ", *dado);
		TFilaPrioridade_Enfileirar(Fila, dado);
	}
	printf("OK.\n");

	printf("Enfileirando itens...");
	dado = (int*)malloc(sizeof(int));
	*dado = 50;
	printf("Item %d. ", *dado);
	TFilaPrioridade_Enfileirar(Fila, dado);
	dado = (int*)malloc(sizeof(int));
	*dado = 51;
	printf("Item %d. ", *dado);
	TFilaPrioridade_Enfileirar(Fila, dado);
	printf("OK.\n");

	printf("Desenfileirando itens...");
	while (Fila->Tamanho > 0)
	{
		dado = (int*)TFilaPrioridade_Desenfileirar(Fila);
		printf("Item %d. ", *dado);
		free(dado);
	}
	printf("OK.\n");

	printf("Destruindo fila...");
	TFilaPrioridade_Destruir(&Fila);
	printf("OK.\n");
	
	exit(EXIT_SUCCESS);
}
