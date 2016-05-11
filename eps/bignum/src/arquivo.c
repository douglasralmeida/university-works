/*
**	MANIPULACAO DE ARQUIVOS
**	DOUGLAS RODRIGUES DE ALMEIDA
**
**	Implementacao de funcoes auxiliares para manipulacao de arquivos
**	
**/

#include <stdio.h>
#include "arquivo.h"

FILE* ArquivoAbrirEscrita(const char* Nome)
{
	return fopen(Nome , "wt");
}

FILE* ArquivoAbrirLeitura(const char* Nome)
{
	return fopen(Nome , "rt");
}

void ArquivoFechar(FILE* Arquivo)
{
	fclose(Arquivo);
}
