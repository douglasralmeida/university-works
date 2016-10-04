/*
**	TESTE DO TAD ARVORE B
**	DOUGLAS RODRIGUES DE ALMEIDA
**
**	Teste do TAD Arvore B
**	
**/

#include <stdio.h>
#include <stdlib.h>
#include "arvoreb.h"

bool CompararInt(void* PInt1, void* PInt2)
{
	return *(int*)PInt1 < *(int*)PInt2;
}


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
	int* p;
	TArvoreB* Arvore;
	
	printf("TESTE ARBORE B\n");
	printf("==============\n");

	printf("Criando arvore...");
	Arvore = TArvoreB_Criar(2);
	Arvore->FuncaoComparar = CompararInt;
	if (Arvore != NULL)
		printf("OK.\n");
	else
		exit(EXIT_FAILURE);

	printf("Inserindo itens na arvore...");
	for (i = 20; i > 1; i--)
	{
		p = malloc(sizeof(int));
		*p = i;
		printf("[%d] ", i);
		TArvoreB_Inserir(Arvore, p);
	}
	printf("OK.\n");

	printf("Destruindo arvore...");
	TArvoreB_Destruir(&Arvore, DestruirInt);
	printf("OK.\n");
	
	exit(EXIT_SUCCESS);
}
