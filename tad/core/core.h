/*
**	TIPOS BASICOS
**	DOUGLAS RODRIGUES DE ALMEIDA
**
**	Tipos basicos
**	
**/

#ifndef CORE_H
#define CORE_H

#include "boolutils.h"

/* Enumerador para ordenacao de listas */
typedef enum {ordCrescente, ordDecresente} TOrdem;

/* Funcao para comparar o valor de dois itens */
typedef bool (*TFuncaoComparar)(void* Dado1, void* Dado2);

/* Funcao para destruir um item */
typedef void (*TFuncaoDestruir)(void** Dado);

/* Funcao para comparar conteudo de dois itens */
typedef bool (*TFuncaoIguais)(void* Dado1, void* Dado2);

/* Funcao para imprimir um item */
typedef void (*TFuncaoImprimir)(void* Dado);

#endif
