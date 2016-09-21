/*
**	BIBLIOTECA DO FILIPE
**	DOUGLAS RODRIGUES DE ALMEIDA
**
**	Implementação do acesso a arquivos
*/

#include <stdio.h>
#include <stdlib.h>
#include "arquivo.h"

TArquivo* TArquivo_Criar(char* Nome, TArquivoModoLeitura Modo)
{
	TArquivo* NovoArquivo;
	
	NovoArquivo = malloc(sizeof(TArquivo));
	switch (Modo)
	{
		case amlBinario:
			NovoArquivo->Inicio = fopen(Nome, "wb");
			NovoArquivo->Final = fopen(Nome, "wb");
		break;
		case amlTexto:
			NovoArquivo->Inicio = fopen(Nome, "wt");
			NovoArquivo->Final = fopen(Nome, "wt");
		break;
	}
	
	return NovoArquivo;
}

void TArquivo_Destruir(TArquivo** PArquivo)
{
	fclose((*PArquivo)->Inicio);
	fclose((*PArquivo)->Final);
	free(*PArquivo);
	PArquivo = NULL;
}

void TArquivo_ApensarNoInicio(TArquivo* Arquivo, void* Dado, size_t TamanhoDado)
{
	rewind(Arquivo->Inicio);	
	fwrite(Dado, TamanhoDado, 1, Arquivo->Inicio);
}

void TArquivo_ApensarNoFinal(TArquivo* Arquivo, void* Dado, size_t TamanhoDado)
{
	fwrite(Dado, TamanhoDado, 1, Arquivo->Final);
}
