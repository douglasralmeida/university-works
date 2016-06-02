/*
**	TIPO ABASTRATO DE DADOS LISTA
**	DOUGLAS RODRIGUES DE ALMEIDA
**
**	Cabecalho e estruturas de lista duplamente encadeada por ponteiros
**	
**/

#ifndef CORE_H
#define CORE_H

/* Funcao para comparar dados */
typedef bool (*TFuncaoComparaPrioridade)(void* Dado1, void* Dado2);

/* Funcao para destruir dado */
typedef void (*TFuncaoDestruir)(void** Dado);

/* Funcao para destruir dado */
typedef void (*TFuncaoImprimir)(void* Dado);

#endif