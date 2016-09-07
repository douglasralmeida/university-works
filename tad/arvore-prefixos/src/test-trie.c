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
	FILE* Arquivo;
	/*char* Palavra;*/
	
	printf("TESTE ARVORE DIGITAL\n");
	printf("====================\n");
	
	printf("Criando arvore...");
	Arvore = TArvoreDigital_Criar();
	if (Arvore != NULL)
		printf("OK.\n");
	else
		exit(EXIT_FAILURE);

	printf("Carregando arvore...");
	Arquivo = fopen("arquivo.dic", "rt");
	if (!Arquivo)
		printf("Erro: Erro ao abrir arquivo.\n");
	else
	{
		TArvoreDigital_CarregarArquivo(Arvore, Arquivo);
		printf("OK.\n");
		fclose(Arquivo);
	}
	/*
	printf("Adicionando palavra...");
	Palavra = malloc(16 * sizeof(char));
	scanf("%15s", Palavra);
	TArvoreDigital_Adicionar(Arvore, Palavra);
	free(Palavra);
	*/
	printf("Contando palavras do texto...");
	Arquivo = fopen("texto.txt", "rt");
	if (!Arquivo)
		printf("Erro: Erro ao abrir arquivo.\n");
	else
	{
		TArvoreDigital_ContarPalavrasArquivo(Arvore, Arquivo);
		printf("OK.\n");
		fclose(Arquivo);
	}	
	
	printf("Destruindo arvore...");
	TArvoreDigital_Destruir(&Arvore);
	printf("OK.\n");
	
	exit(EXIT_SUCCESS);
}
