/*
**	TESTE DO TAD PILHA
**	DOUGLAS RODRIGUES DE ALMEIDA
**
**	Teste do TAD Pilha
**	
**/

#include <stdio.h>
#include <stdlib.h>
#include "pilha.h"

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
	TPilha* Pilha;
	
	FuncaoDestruir = &DestruirInt;
	FuncaoImprimir = &ImprimirInt;
	
	printf("TESTE PILHA\n");
	printf("===========\n");
	
	printf("Criando pilha...");
	Pilha = TPilha_Criar(10);
	if (Pilha != NULL)
		printf("OK.\n");
	else
		exit(EXIT_FAILURE);

	printf("Preenchendo pilha...");
	for (i = 0; i < 10; i++)
	{
		dado = (int*)malloc(sizeof(int));
		*dado = i;
		TPilha_Empilhar(Pilha, dado);
	}
	printf("OK.\n");
	
	printf("Exibindo pilha...");
	TPilha_Imprimir(Pilha, FuncaoImprimir);
	printf("OK.\n");

	printf("Tamanho da pilha...");
	printf("%lu. ", (unsigned long)TPilha_Tamanho(Pilha));
	printf("OK.\n");
	
	printf("Limpando pilha...");
	TPilha_Limpar(Pilha, FuncaoDestruir);
	printf("OK.\n");

	printf("Tamanho da pilha...");
	printf("%lu. ", TPilha_Tamanho(Pilha));
	printf("OK.\n");

	printf("Desempilhando pilha vazia...");
	TPilha_Desempilhar(Pilha);
	
	printf("Preenchendo pilha...");
	for (i = 100; i < 110; i++)
	{
		dado = (int*)malloc(sizeof(int));
		*dado = i;
		TPilha_Empilhar(Pilha, dado);
	}
	printf("OK.\n");

	printf("Exibindo pilha...");
	TPilha_Imprimir(Pilha, FuncaoImprimir);
	printf("OK.\n");
	
	printf("Empilhando pilha cheia...");
	TPilha_Empilhar(Pilha, dado);
	
	printf("Desempilhando pilha...");
	dado = (int*)TPilha_Desempilhar(Pilha);
	printf("Item %d. ", *dado);
	free(dado);
	dado = (int*)TPilha_Desempilhar(Pilha);
	printf("Item %d. ", *dado);
	free(dado);
	printf("OK.\n");

	printf("Tamanho da pilha...");
	printf("%lu. ", (unsigned long)TPilha_Tamanho(Pilha));
	printf("OK.\n");

	printf("Exibindo pilha...");
	TPilha_Imprimir(Pilha, FuncaoImprimir);
	printf("OK.\n");

	printf("Empilhando item...");
	dado = (int*)malloc(sizeof(int));
	*dado = 150;
	TPilha_Empilhar(Pilha, dado);
	printf("OK.\n");

	printf("Tamanho da pilha...");
	printf("%lu. ", (unsigned long)TPilha_Tamanho(Pilha));
	printf("OK.\n");

	printf("Exibindo pilha...");
	TPilha_Imprimir(Pilha, FuncaoImprimir);
	printf("OK.\n");

	printf("Destruindo pilha...");
	TPilha_Destruir(&Pilha, FuncaoDestruir);
	printf("OK.\n");
	
	exit(EXIT_SUCCESS);
}
