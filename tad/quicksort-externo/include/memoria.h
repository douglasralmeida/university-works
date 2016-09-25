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
	size_t Capacidade;
	void** Itens;
	size_t ItensCont;
	size_t Primeiro;
	size_t Ultimo;
} TMemoria;

TMemoria* TMemoria_Criar(size_t Capacidade);

void TMemoria_Destruir(TMemoria** PMemoria);

void TMemoria_Escrever(TMemoria* Memoria, void* Dado);

void TMemoria_EscreverNaOrdem(TMemoria* Memoria, void* Dado);

void* TMemoria_LerPrimeiro(TMemoria* Memoria);

void* TMemoria_LerUltimo(TMemoria* Memoria);


#endif
