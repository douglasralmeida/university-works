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
#include "core.h"
#include "boolutils.h"

/* Estrutura da fila com prioridades */
typedef struct _TFilaPrioridade {
	size_t Capacidade;
	size_t Expansao;
	TFuncaoComparar FuncaoComparar;
	TFuncaoDestruir FuncaoDestruir;
	void** Heap;
	size_t Tamanho;
} TFilaPrioridade;

/* ----------------------------------------------------------------------------
 * funcao:		TFilaPrioridade_Criar
 * 				Cria uma fila com prioridades vazia
 * @param:		(vazio)
 * @retorna:	A filade prioridades alocada
 *---------------------------------------------------------------------------*/ 
TFilaPrioridade* TFilaPrioridade_Criar(size_t Capacidade, TFuncaoComparar FuncaoComparar, TFuncaoDestruir FuncaoDestruir);

/* ----------------------------------------------------------------------------
 * funcao:		TFilaPrioridade_Destruir
 * 				Destroi a fila com prioridades
 * @param:		Ponteiro para o ponteiro da fila
 * @retorna:	(vazio)
 *---------------------------------------------------------------------------*/ 
void TFilaPrioridade_Destruir(TFilaPrioridade** PFila);

/* ----------------------------------------------------------------------------
 * funcao:		TFilaPrioridade_Desenfileirar
 * 				Remove o proximo item da fila com prioridades
 * @param:		Ponteiro para a fila
 * @param:		Item a ser removido
 * @retorna:	(vazio)
 *---------------------------------------------------------------------------*/ 
void* TFilaPrioridade_Desenfileirar(TFilaPrioridade* Fila);

/* ----------------------------------------------------------------------------
 * funcao:		TFilaPrioridade_Enfileirar
 * 				Insere um item na fila com prioridades
 * @param:		Ponteiro para a fila
 * @param:		Item a ser inserido
 * @param:		Prioridade de saida do item a ser inserido
 * @retorna:	(vazio)
 *---------------------------------------------------------------------------*/ 
bool TFilaPrioridade_Enfileirar(TFilaPrioridade* Fila, void* Item);

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
