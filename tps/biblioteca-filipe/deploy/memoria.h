	/*
**	BIBLIOTECA DO FILIPE
**	DOUGLAS RODRIGUES DE ALMEIDA
**
**	Estrutura de dados do simulador de memoria
*/

#ifndef MEMORIA_H
#define MEMORIA_H

#include <stdlib.h>
#include "core.h"

typedef struct _TMemoria {
	size_t Capacidade;
	TFuncaoComparar FuncaoComparar;
	void** Itens;
	size_t ItensCont;
	size_t Primeiro;
	size_t Ultimo;
} TMemoria;

/* aloca na memoria */
TMemoria* TMemoria_Criar(size_t Capacidade);

/* desaloca */
void TMemoria_Destruir(TMemoria** PMemoria);

/* insere um item na ultima posicao livre do vetor memoria */
void TMemoria_Escrever(TMemoria* Memoria, void* Dado);

/* insere um item na ordem na memoria vetor memoria */
void TMemoria_EscreverNaOrdem(TMemoria* Memoria, void* Dado);

/* remove e retorna o primeiro item do vetor memoria */
void* TMemoria_LerPrimeiro(TMemoria* Memoria);

/* remove e retorna o ultimo item do vetor memoria */
void* TMemoria_LerUltimo(TMemoria* Memoria);

#endif
