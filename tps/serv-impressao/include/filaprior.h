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
	TFilaNo* Frente;	
	unsigned int Tamanho;
	unsigned int TiposPrioridade;
} TFilaPrioridade;

/* ----------------------------------------------------------------------------
 * funcao:		TFilaPrioridade_Criar
 * 				Cria uma fila com prioridades vazia
 * @param:		QuantTipoPrioridades: Quantidade de tipos de prioridades
				diferentes.
 * @retorna:	A filade prioridades alocada
 *---------------------------------------------------------------------------*/ 
TFilaPrioridade* TFilaPrioridade_Criar(const unsigned int QuantTipoPrioridades);

/* ----------------------------------------------------------------------------
 * funcao:		TFilaPrioridade_Destruir
 * 				Destroi a fila com prioridades
 * @param:		Ponteiro para o ponteiro da fila
 * @retorna:	(vazio)
 *---------------------------------------------------------------------------*/ 
void TFilaPrioridade_Destruir(TLista** PFila);

/* ----------------------------------------------------------------------------
 * funcao:		TFilaPrioridade_Desenfileirar
 * 				Remove o proximo item da fila com prioridades
 * @param:		Ponteiro para a fila
 * @retorna:	O item removido
 *---------------------------------------------------------------------------*/ 
TFilaItem TFilaPrioridade_Desenfileirar(TFilaPrioridade* Fila);

/* ----------------------------------------------------------------------------
 * funcao:		TFilaPrioridade_Enfileirar
 * 				Insere um item na fila com prioridades
 * @param:		Ponteiro para a fila
 * @param:		Item a ser inserido
 * @param:		Prioridade de saida do item a ser inserido
 * @retorna:	(vazio)
 *---------------------------------------------------------------------------*/ 
void TFilaPrioridade_Enfileirar(TFilaPrioridade* Fila, const TFilaItem Item, const unsigned int Prioridade);

/* ----------------------------------------------------------------------------
 * funcao:		TFilaPrioridade_Imprimir
 * 				Imprime a fila com prioridades na tela
 * @param:		Ponteiro para a fila
 * @retorna:	(vazio)
 *---------------------------------------------------------------------------*/ 
void TFilaPrioridade_Imprimir(TFilaPrioridade* Fila);

/* ----------------------------------------------------------------------------
 * funcao:		TFilaPrioridade_Limpar
 * 				Remove todos os itens da fila com prioridades
 * @param:		Ponteiro para a fila
 * @retorna:	(vazio)
 *---------------------------------------------------------------------------*/ 
void TFilaPrioridade_Limpar(TFilaPrioridade* Fila);

/* ----------------------------------------------------------------------------
 * funcao:		TFilaPrioridade_Tamanho
 * 				Retorna o quantidade de itens da fila com prioridaes
 * @param:		Ponteiro para a fila
 * @retorna:	Inteiro com o tamanho
 *---------------------------------------------------------------------------*/ 
unsigned int TFilaPrioridade_Tamanho(TFilaPrioridade* Fila);

#endif
