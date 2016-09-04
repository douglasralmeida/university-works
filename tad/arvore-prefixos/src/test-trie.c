/*
**	TESTE DO TAD ARVORE DIGITAL
**	DOUGLAS RODRIGUES DE ALMEIDA
**
**	Teste do TAD Arvore Digital
**	
**/

#include <stdio.h>
#include <stdlib.h>
#include "trie.h"

int main(void)
{	
	TArvoreDigital* Arvore;
	
	printf("TESTE ARVORE DIGITAL\n");
	printf("====================\n");
	
	printf("Criando arvore...");
	Arvore = TArvoreDigital_Criar();
	if (Arvore != NULL)
		printf("OK.\n");
	else
		exit(EXIT_FAILURE);

	printf("Destruindo arvore...");
	TArvore_Destruir(&Arvore);
	printf("OK.\n");
	
	exit(EXIT_SUCCESS);
}