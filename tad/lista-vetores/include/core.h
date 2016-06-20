/*
**	TIPO ABASTRATO DE DADOS LISTA
**	DOUGLAS RODRIGUES DE ALMEIDA
**
**	Cabecalho e estruturas de lista duplamente encadeada por ponteiros
**	
**/

#ifndef CORE_H
#define CORE_H

#include "boolutils.h"

/* Funcao para comparar valor dos dados */
typedef bool (*TFuncaoComparar)(void* Dado1, void* Dado2);

/* Funcao para destruir dado */
typedef void (*TFuncaoDestruir)(void** Dado);

/* Funcao para comparar conteudo dos dados */
typedef bool (*TFuncaoIguais)(void* Dado1, void* Dado2);

/* Funcao para destruir dado */
typedef void (*TFuncaoImprimir)(void* Dado);

#endif
