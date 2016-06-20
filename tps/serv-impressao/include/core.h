/*
**	FUNCOES BASICAS
**	DOUGLAS RODRIGUES DE ALMEIDA
**	
**	Metodos callback para TADs implementados
**	
**/

#ifndef CORE_H
#define CORE_H

#include "boolutils.h"

/* Funcao para comparar valor dos dados */
/* Retorna 1 se Dado1 possui maior valor, 0 se contrario */
typedef bool (*TFuncaoComparar)(void* Dado1, void* Dado2);

/* Funcao para destruir dado */
typedef void (*TFuncaoDestruir)(void** Dado);

/* Funcao para comparar conteudo dos dados */
/* Retorna 1 se Dado1 e Dado2 sao iguais, 0 se contrario */
typedef bool (*TFuncaoIguais)(void* Dado1, void* Dado2);

/* Funcao para destruir dado */
typedef void (*TFuncaoImprimir)(void* Dado);

#endif
