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

int main()
{
	struct timeval tvalDepois, tvalAntes;
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
	gettimeofday (&tvalAntes, NULL);
	TArvoreDigital_CarregarTela(Arvore);
	gettimeofday (&tvalDepois, NULL);
	
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
				
	printf("Time: %ld microsegundos\n",
            ((tvalDepois.tv_sec - tvalAntes.tv_sec)*1000000L
           +tvalDepois.tv_usec) - tvalAntes.tv_usec);	
	
	/*Limpar a bagunça*/
	TArvoreDigital_Destruir(&Arvore);
	exit(EXIT_SUCCESS);
}
