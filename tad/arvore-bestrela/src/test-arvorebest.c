/*
**	TESTE DO TAD ARVORE B ESTRELA
**	DOUGLAS RODRIGUES DE ALMEIDA
**
**	Teste do TAD Arvore B*
**	
**/

#include <stdio.h>
#include <stdlib.h>
#include "arvorebest.h"

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
	TArvoreBE* ArvoreBE;
	TFuncaoDestruir FuncaoDestruir;
	
	printf("TESTE ARBORE B*\n");
	printf("===============\n");

	FuncaoDestruir = DestruirInt;	

	printf("Criando arvore...");
	ArvoreBE = TArvoreBE_Criar(70);
	if (ArvoreBE != NULL)
		printf("OK.\n");
	else
		exit(EXIT_FAILURE);

	printf("Destruindo arvore...");
	TArvoreBE_Destruir(&ArvoreBE, FuncaoDestruir);
	printf("OK.\n");
	
	exit(EXIT_SUCCESS);
}
