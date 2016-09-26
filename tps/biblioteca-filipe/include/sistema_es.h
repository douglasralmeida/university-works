/*
**	BIBLIOTECA DO FILIPE
**	DOUGLAS RODRIGUES DE ALMEIDA
**
**	Estrutura de dados do de entrada e saida em arquivo
*/

#ifndef SISTEMA_ES_H
#define SISTEMA_ES_H

#include "boolutils.h"
#include <stdio.h>

typedef enum {
	esmBinarioEscrita, 
	esmBinarioLeitura,
	esmTextoEscrita,
	esmTextoLeitura
} TESModo;

typedef struct _TSistemaManipuladorES {
	FILE* Arquivo;
} TSistemaManipuladorES;

TSistemaManipuladorES* TSistemaManipuladorES_Criar(char* Nome, TESModo Modo);

void TSistemaManipuladorES_Destruir(TSistemaManipuladorES** PManipulador);

/*void TArquivo_ApensarNoInicio(TArquivo* Arquivo, void* Dado, size_t TamanhoDado);*/

bool TSistemaManipuladorES_ExportarFinal(TSistemaManipuladorES* Manipulador, void* Dado, size_t TamanhoDado);

bool TSistemaManipuladorES_ImportarProximo(TSistemaManipuladorES* Manipulador, void* Dado, size_t TamanhoDado);

#endif
