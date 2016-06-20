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

bool IguaisInt(void* PInt1, void* PInt2)
{
	int* Int1;
	int* Int2;

	Int1 = (int*)PInt1;
	Int2 = (int*)PInt2;
	return (*Int1 == *Int2);
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
	TFuncaoIguais FuncaoIguais;
	TFuncaoImprimir FuncaoImprimir;
	TLista* Lista;
	
	FuncaoDestruir = &DestruirInt;
	FuncaoIguais = &IguaisInt;
	FuncaoImprimir = &ImprimirInt;
	
	printf("TESTE LISTA\n");
	printf("===========\n");
	
	printf("Criando lista...");
	Lista = TLista_Criar(FuncaoDestruir, FuncaoIguais, FuncaoImprimir);
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
