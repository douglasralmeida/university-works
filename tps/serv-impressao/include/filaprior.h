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
typedef struct _TFilaPrioridadeNo TFilaPrioridadeNo;

struct _TFilaPrioridadeNo {
	TFilaItem Item;
	TFilaPrioridadeNo* Esquerda;
	TFilaPrioridadeNo* Direita;
};

/* Estrutura da fila com prioridades */
typedef struct _TFilaPrioridade {
	TFilaPrioridadeNo* Frente;
	size_t Tamanho;
} TFilaPrioridade;

/* ----------------------------------------------------------------------------
 * funcao:		TFilaPrioridade_Criar
 * 				Cria uma fila com prioridades vazia
 * @param:		(vazio)
 * @retorna:	A filade prioridades alocada
 *---------------------------------------------------------------------------*/ 
TFilaPrioridade* TFilaPrioridade_Criar(void);

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
 * @param:		Item a ser removido
 * @retorna:	(vazio)
 *---------------------------------------------------------------------------*/ 
void TFilaPrioridade_Desenfileirar(TFilaPrioridade* Fila, TItem* Item);

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
size_t TFilaPrioridade_Tamanho(TFilaPrioridade* Fila);

#endif