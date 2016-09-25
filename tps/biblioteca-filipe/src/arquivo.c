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
	if (!NovoArquivo)
		return NULL;
	switch (Modo)
	{
		case amlBinario:
			NovoArquivo->Descritor = fopen(Nome, "wb");
		break;
		case amlTexto:
			NovoArquivo->Descritor = fopen(Nome, "r+w");
		break;
	}
	if (!NovoArquivo->Descritor)
	{
		free(NovoArquivo);
		return NULL;
	}	
	return NovoArquivo;
}

void TArquivo_Destruir(TArquivo** PArquivo)
{
	fflush((*PArquivo)->Descritor);
	fclose((*PArquivo)->Descritor);
	free(*PArquivo);
	*PArquivo = NULL;
}

void TArquivo_ApensarNoInicio(TArquivo* Arquivo, void* Dado, size_t TamanhoDado)
{
	rewind(Arquivo->Descritor);	
	fwrite(Dado, TamanhoDado, 1, Arquivo->Descritor);
}

void TArquivo_ApensarAgora(TArquivo* Arquivo, void* Dado, size_t TamanhoDado)
{
	fwrite(Dado, TamanhoDado, 1, Arquivo->Descritor);
}
