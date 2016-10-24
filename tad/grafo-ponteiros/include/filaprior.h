/*
 *	TIPO ABASTRATO DE DADOS FILA COM PRIORIDADES
 *	DOUGLAS RODRIGUES DE ALMEIDA
 *
 *	Cabeçalho e estruturas da fila com prioridades
 *	
 */

#ifndef FILAPRIO_H
#define FILAPRIO_H

#include <stdlib.h>
#include "core.h"
#include "boolutils.h"

/* Estrutura da fila com prioridades */
typedef struct _TFilaPrioridade {
	size_t Capacidade;			/*-- Capacidade de armazenamento atual da fila --*/
	size_t Expansao;			/*-- Quantidade a ser expandida pela fila --*/
	TFuncaoComparar FuncaoComparar;		/*-- Funcao que compara o valor de dois itens da fila --*/
	void** Heap;				/*-- Heap da fila de prioridades --*/
	size_t Tamanho;				/*-- Tamanho da fila --*/
} TFilaPrioridade;

/* ----------------------------------------------------------------------------
 * funcao:		TFilaPrioridade_Criar
 * 			Cria uma fila com prioridades vazia
 * @param:		Capacidade inicial da fila
 * @param:		Funcao de comparacao de dois itens da fila
 * @retorna:		A filade com prioridades alocada
 *---------------------------------------------------------------------------*/ 
TFilaPrioridade* TFilaPrioridade_Criar(size_t Capacidade, TFuncaoComparar FuncaoComparar);

/* ----------------------------------------------------------------------------
 * funcao:		TFilaPrioridade_Destruir
 * 			Destroi a fila com prioridades
 * @param:		Fila
 * @param:		Funcao que destrói itens da fila
 * @retorna:		(vazio)
 *---------------------------------------------------------------------------*/ 
void TFilaPrioridade_Destruir(TFilaPrioridade** PFila, TFuncaoDestruir FuncaoDestruir);

/* ----------------------------------------------------------------------------
 * funcao:		TFilaPrioridade_Desenfileirar
 * 			Remove o proximo item da fila com prioridades
 * @param:		Fila
 * @param:		Item a ser removido
 * @retorna:		(vazio)
 *---------------------------------------------------------------------------*/ 
void* TFilaPrioridade_Desenfileirar(TFilaPrioridade* Fila);

/* ----------------------------------------------------------------------------
 * funcao:		TFilaPrioridade_Enfileirar
 * 			Insere um item na fila com prioridades
 * @param:		Fila
 * @param:		Item a ser inserido
 * @retorna:		True em caso de inserção com sucesso, false em caso de falha
 *---------------------------------------------------------------------------*/ 
bool TFilaPrioridade_Enfileirar(TFilaPrioridade* Fila, void* Item);

/* ----------------------------------------------------------------------------
 * funcao:		TFilaPrioridade_Limpar
 *			Remove todos os itens da fila com prioridades
 * @param:		Fila
 * @param:		Função que destrói itens da fila
 * @retorna:		(vazio)
 *---------------------------------------------------------------------------*/ 
void TFilaPrioridade_Limpar(TFilaPrioridade* Fila, TFuncaoDestruir FuncaoDestruir);

/* ----------------------------------------------------------------------------
 * funcao:		TFilaPrioridade_Tamanho
 * 			Retorna o quantidade de itens da fila com prioridaes
 * @param:		Fila
 * @retorna:		Seu tamanho
 *---------------------------------------------------------------------------*/ 
size_t TFilaPrioridade_Tamanho(TFilaPrioridade* Fila);

#endif
