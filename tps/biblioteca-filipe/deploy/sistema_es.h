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
	TESModo Modo;
} TSistemaManipuladorES;

TSistemaManipuladorES* TSistemaManipuladorES_Criar(char* Nome, TESModo Modo);

void TSistemaManipuladorES_Destruir(TSistemaManipuladorES** PManipulador);

/*void TArquivo_ApensarNoInicio(TArquivo* Arquivo, void* Dado, size_t TamanhoDado);*/

/* salva um registro no fim daorigem de dados */
bool TSistemaManipuladorES_ExportarFinal(TSistemaManipuladorES* Manipulador, void* Dado, size_t TamanhoDado);

/* retorna o proximo registro da origem de dados */
bool TSistemaManipuladorES_ImportarProximo(TSistemaManipuladorES* Manipulador, void* Dado, size_t TamanhoDado);

/* retorna a quantidade de registros */
size_t TSistemaManipuladorES_ItensQuantidade(TSistemaManipuladorES* Manipulador, size_t TamanhoDado);

#endif
