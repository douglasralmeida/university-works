/*
**	TESTE DO TAD LISTA
**	DOUGLAS RODRIGUES DE ALMEIDA
**
**	Teste do TAD Lista
**	
**/

#include <stdio.h>
#include <stdlib.h>
#include "list.h"

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
	TLista* Lista;
	
	FuncaoDestruir = &DestruirInt;
	FuncaoImprimir = &ImprimirInt;
	
	printf("TESTE LISTA\n");
	printf("===========\n");
	
	printf("Criando lista...");
	Lista = TLista_Criar(FuncaoDestruir, FuncaoImprimir);
	if (Lista != NULL)
		printf("OK.\n");
	else
		exit(EXIT_FAILURE);

	printf("Preenchendo lista...");
	for (i = 0; i < 10; i++)
	{
		dado = (int*)malloc(sizeof(int));
		*dado = i;
		TLista_Adicionar(Lista, dado);
	}
	printf("OK.\n");
	
	printf("Exibindo lista...");
	TLista_Imprimir(Lista);
	printf("OK.\n");
	
	printf("Limpando lista...");
	TLista_Limpar(Lista);
	printf("OK.\n");
	
	printf("Preenchendo lista...");
	for (i = 100; i < 110; i++)
	{
		dado = (int*)malloc(sizeof(int));
		*dado = i;
		TLista_Adicionar(Lista, dado);
	}
	printf("OK.\n");

	printf("Exibindo lista...");
	TLista_Imprimir(Lista);
	printf("OK.\n");

	printf("Destruindo lista...");
	TLista_Destruir(&Lista);
	printf("OK.\n");
	
	exit(EXIT_SUCCESS);
}
