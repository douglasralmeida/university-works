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
	TArvoreBEstrela* ArvoreBEstrela;
	TFuncaoDestruir FuncaoDestruir;
	
	printf("TESTE ARBORE B*\n");
	printf("===============\n");

	FuncaoDestruir = DestruirInt;	

	printf("Criando arvore...");
	ArvoreBEstrela = TArvoreBEstrela_Criar(3);
	if (ArvoreBEstrela != NULL)
		printf("OK.\n");
	else
		exit(EXIT_FAILURE);

	printf("Destruindo arvore...");
	TArvoreBEstrela_Destruir(&ArvoreBEstrela, FuncaoDestruir);
	printf("OK.\n");
	
	exit(EXIT_SUCCESS);
}
