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
	unsigned long quantdic, quanttexto;
	TArvoreDigital* Arvore;

	/*Criar arvore na memoria*/
	Arvore = TArvoreDigital_Criar();
	if (!Arvore)
		exit(EXIT_FAILURE);
	/*Carregar o dicionario do stdin*/
	scanf("%lu", &quantdic);
	getchar();
	/*entrada = malloc(16 * quantdic * sizeof(char));
	if (!entrada)
	{
		TArvoreDigital_Destruir(&Arvore);
		exit(EXIT_FAILURE);
	}	
	scanf("%s", entrada);*/	
	TArvoreDigital_CarregarTela(Arvore);
		
	/*Carregar o texto do stdin e processar*/
	scanf("%lu", &quanttexto);
	getchar();
	
	/*entrada = malloc(16 * quanttexto * sizeof(char));
	if (!entrada)
	{
		TArvoreDigital_Destruir(&Arvore);
		exit(EXIT_FAILURE);	
	}
	scanf("%s", entrada);*/
	TArvoreDigital_ContarPalavrasTela(Arvore);
		
	/*Imprimir resultado na tela*/
	TArvoreDigital_ExibirContador(Arvore);
	
	/*Limpar a bagunça*/
	TArvoreDigital_Destruir(&Arvore);
	exit(EXIT_SUCCESS);
}
