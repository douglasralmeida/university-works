/*
**	FREQUENCIA DE PALAVRAS
**	DOUGLAS RODRIGUES DE ALMEIDA
**
**	Aplicativo de testes de stress
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include "trie.h"

int main(int argc, char *argv[])
{
	TArvoreDigital* Arvore;
	FILE* Arquivo;

	/*Criar arvore na memoria*/
	Arvore = TArvoreDigital_Criar();
	if (!Arvore)
		exit(EXIT_FAILURE);

	printf("arquivo: %s ", argv[1]);
	Arquivo = fopen(argv[1], "rt");
	if (Arquivo)
	{
		TArvoreDigital_CarregarArquivo(Arvore, Arquivo);
		printf("OK\n");
	}
	else
		printf("ERRO\n");
	
	/*Limpar a bagunça*/
	TArvoreDigital_Destruir(&Arvore);
	exit(EXIT_SUCCESS);
}
