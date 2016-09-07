/*
**	FREQUENCIA DE PALAVRAS
**	DOUGLAS RODRIGUES DE ALMEIDA
**
**	Aplicativo principal
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "trie.h"

int main()
{
	unsigned long long i, quantdic, quanttexto; /* suportar 10^16 palavras */
	char** palavras; /* guarda as palavras na ordem de entrada */
	TArvoreDigital* Arvore;

	/*Criar arvore na memoria*/
	Arvore = TArvoreDigital_Criar();
	if (!Arvore)
		exit(EXIT_FAILURE);
		
	/*Carregar o dicionario do stdin*/
	scanf("%llu", &quantdic);
	getchar();
	palavras = malloc(quantdic * sizeof(char*));
	for (i = 0; i < quantdic; i++)
	{
		palavras[i] = malloc(16 * sizeof(char));
		scanf("%s", palavras[i]);
		TArvoreDigital_CarregarString(Arvore, palavras[i]);
	}
		
	/*Carregar o texto do stdin e processar*/
	scanf("%llu", &quanttexto);
	getchar();	
	TArvoreDigital_ContarPalavrasTela(Arvore);
		
	/*Imprimir resultado na tela*/
	for (i = 0; i < quantdic; i++)
	{
		TArvoreDigital_ExibirContador(Arvore, palavras[i]);
		free(palavras[i]);
	}	
	
	/*Limpar a bagunça*/
	free(palavras);
	TArvoreDigital_Destruir(&Arvore);
	exit(EXIT_SUCCESS);
}
