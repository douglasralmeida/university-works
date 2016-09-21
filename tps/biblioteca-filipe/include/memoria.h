/*
**	BIBLIOTECA DO FILIPE
**	DOUGLAS RODRIGUES DE ALMEIDA
**
**	Estrutura de dados do simulador de memoria
*/

#ifndef MEMORIA_H
#define MEMORIA_H

#include <stdlib.h>

typedef struct _TMemoria {
	size_t Tamanho;
	void** Itens;
} TMemoria;

TMemoria* TMemoria_Criar(size_t Tamanho);

void TMemoria_Destruir(TMemoria** PMemoria);

void TMemoria_Escrever(TMemoria* Memoria, size_t Posicao, void* Dado);

void* TMemoria_Ler(TMemoria* Memoria, size_t Posicao);

#endif
