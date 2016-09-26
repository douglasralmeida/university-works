/*
**	BIBLIOTECA DO FILIPE
**	DOUGLAS RODRIGUES DE ALMEIDA
**
**	Implementação da entrada e saida de dados em arquivo
*/

#include <stdlib.h>
#include "sistema_es.h"

TSistemaManipuladorES* TSistemaManipuladorES_Criar(char* Nome, TESModo Modo)
{
	TSistemaManipuladorES* NovoManipulador;
	
	NovoManipulador = malloc(sizeof(TSistemaManipuladorES));
	if (!NovoManipulador)
		return NULL;
	switch (Modo)
	{
		case esmBinarioEscrita:
			NovoManipulador->Arquivo = fopen(Nome, "wb");
		break;
		case esmBinarioLeitura:
			NovoManipulador->Arquivo = fopen(Nome, "rb");
		break;
		case esmTextoEscrita:
			NovoManipulador->Arquivo = fopen(Nome, "w");
		break;
		case esmTextoLeitura:
			NovoManipulador->Arquivo = fopen(Nome, "r");
		break;
	}
	if (!NovoManipulador->Arquivo)
	{
		free(NovoManipulador);
		return NULL;
	}	
	return NovoManipulador;
}

void TSistemaManipuladorES_Destruir(TSistemaManipuladorES** PManipulador)
{
	fclose((*PManipulador)->Arquivo);
	free(*PManipulador);
	*PManipulador = NULL;
}
/*
void TArquivo_ApensarNoInicio(TArquivo* Arquivo, void* Dado, size_t TamanhoDado)
{
	rewind(Arquivo->Descritor);	
	fwrite(Dado, TamanhoDado, 1, Arquivo->Descritor);
}*/

bool TSistemaManipuladorES_ExportarFinal(TSistemaManipuladorES* Manipulador, void* Dado, size_t TamanhoDado)
{
	return (fwrite(Dado, TamanhoDado, 1, Manipulador->Arquivo) > 0);
}

bool TSistemaManipuladorES_ImportarProximo(TSistemaManipuladorES* Manipulador, void* Dado, size_t TamanhoDado)
{
	return (fread(Dado, TamanhoDado, 1, Manipulador->Arquivo) > 0);
}
