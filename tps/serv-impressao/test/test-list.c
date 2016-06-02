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
	free(*PInt);
	PInt = NULL;
}

void ImprimirInt(void* PInt)
{
	printf("%d ", (int)(*PInt));
}

int main(int argc, char *argv[])
{	
	int j;
	int* i;
	TFuncaoDestruir FuncaoDestruir;
	TFuncaoImprimir FuncaoImprimir;
	TLista* Lista;
	
	FuncaoDestruir = &DestruirInt;
	TFuncaoImprimir = &ImprimirInt;
	
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
		i = (int*)malloc(sizeof(int));
		*i = j;
		TLista_Adicionar(i);
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
		i = (int*)malloc(sizeof(int));
		*i = j;
		TLista_Adicionar(i);
	}
	printf("OK.\n");

	printf("Exibindo lista...");
	TLista_Imprimir(Lista);
	printf("OK.\n");

	printf("Destruindo lista...");
	TLista_Limpar(Lista);
	printf("OK.\n");
	
	exit(EXIT_SUCCESS);
}
