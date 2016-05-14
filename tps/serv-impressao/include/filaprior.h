/*
 *	TIPO ABASTRATO DE DADOS FILA COM PRIORIDADE
 *	DOUGLAS RODRIGUES DE ALMEIDA
 *
 *	Cabecalho e estruturas da fila com prioridade
 *	
 */

#ifndef FILAPRIOR_H
#define FILAPRIOR_H

#include <stdio.h>
#include <stdlib.h>
#include "boolutils.h"
#include "item.h"

/* Estrutura do no da fila */
typedef struct _TFilaNo TFilaNo;

struct _TFilaNo {
	TFilaItem Item;
	TFilaNo* Proximo;
};

/* Estrutura da fila virtual */
typedef struct _TFilaVirtual {
	TFilaNo* Frente;
	TFilaNo* Tras;
} TFilaVirtual;

/* Estrutura da fila com prioridades */
typedef struct _TFilaPrioridade {
	TFilaVirtual* FilasVirtuais;
	unsigned int Prioridades;
	unsigned int Tamanho;
	TFilaNo* Primeiro;
	TFilaNo* Ultimo;
} TFilaPrioridade;

/* Cria uma fila com prioridades vazia */
TFilaPrioridade* TFilaPrioridade_Criar(const unsigned int QuantTipoPrioridades);

/* Destroi a fila com prioridades */
void TFilaPrioridade_Destruir(TLista** PFila);

/* Remove um item da fila com prioridades */
TFilaItem TFilaPrioridade_Desenfileirar(TFilaPrioridade* Fila);

/* Adidiona um item a fila com prioridades */
void TFilaPrioridade_Enfileirar(TFilaPrioridade* Fila, const TFilaItem Item, const int Prioridade);

/* Imprime a fila com prioridades na tela */
void TFilaPrioridade_Imprimir(TFilaPrioridade* Fila);

/* Remove todos os itens da fila com prioridades */
void TFilaPrioridade_Limpar(TFilaPrioridade* Fila);

/* Retorna o quantidade de itens da fila com prioridaes */
unsigned int TFilaPrioridade_Tamanho(TFilaPrioridade* Fila);

#endif
