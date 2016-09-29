/*
**	TESTE DO TAD ARVORE B MAIS
**	DOUGLAS RODRIGUES DE ALMEIDA
**
**	Teste do TAD Arvore B+
**	
**/

#include <stdio.h>
#include <stdlib.h>
#include "arvorebmais.h"

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
	TArvoreBMais* ArvoreBMais;
	TFuncaoDestruir FuncaoDestruir;
	
	printf("TESTE ARBORE B+\n");
	printf("===============\n");

	FuncaoDestruir = DestruirInt;	

	printf("Criando arvore...");
	ArvoreBMais = TArvoreBMais_Criar(70);
	if (ArvoreBMais != NULL)
		printf("OK.\n");
	else
		exit(EXIT_FAILURE);

	printf("Destruindo arvore...");
	TArvoreBMais_Destruir(&ArvoreBMais, FuncaoDestruir);
	printf("OK.\n");
	
	exit(EXIT_SUCCESS);
}
