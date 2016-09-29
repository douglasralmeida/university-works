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

/* Funcao para comparar o valor de dois itens, returnando true se Dado1 valer menos */
typedef bool (*TFuncaoComparar)(void* Dado1, void* Dado2);

/* Funcao para copiar o conteúdo itens, Dado1 para Dado2 */
typedef void (*TFuncaoCopiar)(void* Dado1, void* Dado2);

/* Funcao para destruir um item */
typedef void (*TFuncaoDestruir)(void** Dado);

/* Funcao para comparar conteudo de dois itens, retornando true se forem iguais */
typedef bool (*TFuncaoIguais)(void* Dado1, void* Dado2);

/* Funcao para imprimir um item */
typedef void (*TFuncaoImprimir)(void* Dado);

#endif
