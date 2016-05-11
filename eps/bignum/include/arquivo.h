/*
**	MANIPULACAO DE ARQUIVOS
**	DOUGLAS RODRIGUES DE ALMEIDA
**
**	Cabecalho de funcoes auxiliares para manipulacao de arquivos
**	
**/

#ifndef ARQUIVO_H
#define ARQUIVO_H

#include <stdlib.h>

/* Abre o arquivo apenas para leitura */
FILE* ArquivoAbrirLeitura(const char* Nome);

/* Abre o arquivo para escrita */
FILE* ArquivoAbrirEscrita(const char* Nome);

/* Fecha o arquivo */
void ArquivoFechar(FILE* Arquivo);

#endif
