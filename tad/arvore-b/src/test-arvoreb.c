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

bool IgualInt(void* PInt1, void* PInt2)
{
	return *(int*)PInt1 == *(int*)PInt2;
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
	int* p, *x;
	TArvoreB* Arvore;
	
	printf("TESTE ARBORE B\n");
	printf("==============\n");

	printf("Criando arvore...");
	Arvore = TArvoreB_Criar(3);
	Arvore->FuncaoComparar = CompararInt;
	Arvore->FuncaoIguais = IgualInt;
	if (Arvore != NULL)
		printf("OK.\n");
	else
		exit(EXIT_FAILURE);

	printf("Inserindo itens na arvore...");
	for (i = 50; i > 0; i = i-2)
	{
		p = malloc(sizeof(int));
		*p = i;
		printf("[%d] ", i);
		TArvoreB_Inserir(Arvore, p);
	}
	printf("OK.\n");

	printf("Exibindo arvore...\n");
	TArvoreB_Imprimir(Arvore, ImprimirInt);
	printf("OK.\n");

	printf("Pesquisando na arvore...");
	x = malloc(sizeof(int));

	*x = 4;
	printf("[%d: ", *x);
	if ((p = TArvoreB_Pesquisar(Arvore, x)) != NULL)
	{
		printf("SIM (%d)] ", *p);
	}
	else
		printf("NAO] ");
	*x = 19;
	printf("[%d: ", *x);
	if ((p = TArvoreB_Pesquisar(Arvore, x)) != NULL)
	{
		printf("SIM (%d)] ", *p);
	}
	else
		printf("NAO] ");

	*x = 10;
	printf("[%d: ", *x);
	if ((p = TArvoreB_Pesquisar(Arvore, x)) != NULL)
	{
		printf("SIM (%d)] ", *p);
	}
	else
		printf("NAO] ");


	free(x);
	printf("OK.\n");
	printf("Destruindo arvore...");
	TArvoreB_Destruir(&Arvore, DestruirInt);
	printf("OK.\n");
	
	exit(EXIT_SUCCESS);
}
