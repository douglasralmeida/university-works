/*
**	TESTE DO TAD LISTA
**	DOUGLAS RODRIGUES DE ALMEIDA
**
**	Teste do TAD Lista
**	
**/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "core.h"
#include "list.h"

bool CompararInt(void* PInt1, void* PInt2)
{
	int* Int1;
	int* Int2;
	
	Int1 = (int*)PInt1;
	Int2 = (int*)PInt2;
	return (*Int1 < *Int2);
}

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
	TFuncaoComparar FuncaoComparar;
	TFuncaoDestruir FuncaoDestruir;
	TFuncaoIguais FuncaoIguais;
	TFuncaoImprimir FuncaoImprimir;
	
	TLista* Lista;
	TListaNo No;
	
	FuncaoComparar = &CompararInt;
	FuncaoDestruir = &DestruirInt;
	FuncaoIguais = &IguaisInt;
	FuncaoImprimir = &ImprimirInt;
	
	printf("TESTE LISTA\n");
	printf("===========\n");
	
	printf("Criando lista...");
	Lista = TLista_Criar(10);
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
	TLista_Imprimir(Lista, FuncaoImprimir);
	printf("OK.\n");
	
	printf("Pesquisando na lista...");
	dado = (int*)malloc(sizeof(int));
	*dado = 5;
	printf(" item %d ", *dado);
	if (TLista_Pesquisar(Lista, (void*)dado, FuncaoIguais) > 0)
		printf(" = encontrado -");
	else
		printf(" = nao encontrado -");
	*dado = 11;
	printf(" item %d ", *dado);
	if (TLista_Pesquisar(Lista, (void*)dado, FuncaoIguais) > 0)
		printf(" = encontrado. ");
	else
		printf(" = nao encontrado. ");
	free(dado);
	printf("OK.\n");

	printf("Removendo da lista...");
	dado = (int*)malloc(sizeof(int));
	*dado = 6;
	printf(" item %d ", *dado);
	No = TLista_Pesquisar(Lista, (void*)dado, FuncaoIguais);
	TLista_Remover(Lista, No, FuncaoDestruir);
	free(dado);
	printf("OK.\n");
	
	printf("Exibindo lista...");
	TLista_Imprimir(Lista, FuncaoImprimir);
	printf("OK.\n");
	
	printf("Limpando lista...");
	TLista_Limpar(Lista, FuncaoDestruir);
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
	TLista_Imprimir(Lista, FuncaoImprimir);
	printf("OK.\n");

	printf("Limpando lista...");
	TLista_Limpar(Lista, FuncaoDestruir);
	printf("OK.\n");
	
	/* ordenacao */
	srand(time(NULL));
	printf("Preenchendo lista...");
	for (i = 0; i < 10; i++)
	{
		dado = (int*)malloc(sizeof(int));
		*dado = rand() % 100;
		TLista_Adicionar(Lista, dado);
	}
	printf("OK.\n");

	printf("Exibindo lista...");
	TLista_Imprimir(Lista, FuncaoImprimir);
	printf("OK.\n");

	printf("Ordenando lista...");
	TLista_Ordenar(Lista, FuncaoComparar);
	printf("OK.\n");

	printf("Exibindo lista...");
	TLista_Imprimir(Lista, FuncaoImprimir);
	printf("OK.\n");
	
	printf("Destruindo lista...");
	TLista_Destruir(&Lista, FuncaoDestruir);
	printf("OK.\n");
	
	exit(EXIT_SUCCESS);
}
