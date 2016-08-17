/*
 *	ALGORITMOS DE CASAMENTO DE CADEIA DE CARACTERES
 *	DOUGLAS RODRIGUES DE ALMEIDA
 *
 *	Teste dos algoritmos para casamento de cadeia de caracteres
 */

#include <stdio.h>
#include <stdlib.h>
#include "caracteres.h"

int main(void)
{
	FILE* Arquivo;
	long TamanhoTexto;
	long TamanhoPalavra;
	char* PalavraPesquisa;
	char* Texto;
	
	printf("Teste de casamento de cadeia de caracteres\n");
	printf("==========================================\n\n");
	
	Arquivo = fopen("texto.txt", "rb");
	if (Arquivo)
	{
		TamanhoTexto = 1;
		Texto = malloc(TamanhoTexto * sizeof(char));
		fclose(Arquivo);
	
		TamanhoPalavra = 129;
		PalavraPesquisa = malloc(TamanhoPalavra * sizeof(char));
		printf("Digite uma palavra (max. 128 car.) para pesquisar:");
		scanf("", );

		free(PalavraPesquisa);
		free(Texto);		
	}	
	exit(EXIT_SUCCESS);
}