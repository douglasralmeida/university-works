/*
**	FREQUENCIA DE PALAVRAS
**	DOUGLAS RODRIGUES DE ALMEIDA
**
**	Aplicativo principal
*/

#include <stdio.h>
#include <stdlib.h>
#include "trie.h"

int main(int argc, char *argv[])
{
	char* palavra;
	unsigned long i, quantdic, quanttexto;
	TArvoreDigital* Arvore;

	Arvore = TArvoreDigital_Criar();
	if (!Arvore)
		exit(EXIT_FAILURE);
	palavra = malloc(16 * sizeof(char));
	if (!palavra)
		exit(EXIT_FAILURE);
	scanf("%lu", &quantdic);
	for (i = 0; i < quantidic; i++)
	{
		scanf("%s", &palavra);
	}
	scanf("%lu", &quanttexto);
	for (i = 0; i < quanttexto; i++)
	{
		scanf("%s", &palavra);
	}
	free(palavra);
	TArvoreDigital_Destruir(&Arvore);
	exit(EXIT_SUCCESS);
}
