/*
**	BIBLIOTECA DO FILIPE
**	DOUGLAS RODRIGUES DE ALMEIDA
**
**	Estrutura de dados do acesso a arquivos
*/

#ifndef ARQUIVO_H
#define ARQUIVO_H

#include <stdio.h>

typedef enum {amlBinario, amlTexto} TArquivoModoLeitura;

typedef struct _TArquivo {
	FILE* Inicio;
	FILE* Final;
} TArquivo;

TArquivo* TArquivo_Criar(char* Nome, TArquivoModoLeitura Modo);

void TArquivo_Destruir(TArquivo** PArquivo);

void TArquivo_ApensarNoInicio(TArquivo* Arquivo, void* Dado, size_t TamanhoDado);

void TArquivo_ApensarNoFinal(TArquivo* Arquivo, void* Dado, size_t TamanhoDado);

#endif
