/*
 *	TIPO ABSTRATO DE DADOS FILA
 *	DOUGLAS RODRIGUES DE ALMEIDA
 *
 *	Cabeçalhos e estruturas de uma fila por vetores
 */

#ifndef FILA_H
#define FILA_H

#include "boolutils.h"
#include "core.h"

#define FILA_EXPANSAO 1024

typedef size_t TFilaNo;

/* Estrutura da fila */
typedef struct _TFila {
	size_t Capacidade;	/*-- Capacidade de armazenamento atual da fila --*/
	size_t Expansao;	/*-- Capacidade de autoexpansão da fila --*/
	TFilaNo Frente;		/*-- Primeiro item da fila --*/
	void** Itens;		/*-- Conteúdo da fila --*/
	size_t Tamanho;		/*-- Tamanho da fila --*/
	TFilaNo Tras;		/*-- Ultimo item da fila --*/
} TFila;

/* ----------------------------------------------------------------------------
 * funcao:		TFila_Criar
 * 			Cria uma fila vazia
 * @param:		Capacidade inicial da fila
 * @retorna:		A fila alocada
 *---------------------------------------------------------------------------*/ 
TFila* TFila_Criar(size_t Capacidade);

/* ----------------------------------------------------------------------------
 * funcao:		TFila_Destruir
 * 			Destroi a fila
 * @param:		Fila
 * @param:		Funcao que destroi um item da fila
 * @retorna:		(vazio)
 *---------------------------------------------------------------------------*/ 
void TFila_Destruir(TFila** PFila, TFuncaoDestruir FuncaoDestruir);

/* ----------------------------------------------------------------------------
 * funcao:		TFila_Desenfileirar
 * 			Remove e retorna o proximo item da fila
 * @param:		Fila
 * @retorna:		Item removido
 *---------------------------------------------------------------------------*/ 
void* TFila_Desenfileirar(TFila* Fila);

/* ----------------------------------------------------------------------------
 * funcao:		TFila_Enfileirar
 * 			Insere um item no final da fila
 * @param:		Fila
 * @param:		Item a ser inserido
 * @retorna:		(vazio)
 *---------------------------------------------------------------------------*/ 
bool TFila_Enfileirar(TFila* Fila, void* Item);

/* ----------------------------------------------------------------------------
 * funcao:		TFila_Imprimir
 * 			Imprime a fila na tela
 * @param:		Fila
 * @param:		Funcao que imprime um item da fila
 * @retorna:		(vazio)
 *---------------------------------------------------------------------------*/ 
void TFila_Imprimir(TFila* Fila, TFuncaoImprimir FuncaoImprimir);

/* ----------------------------------------------------------------------------
 * funcao:		TFila_Limpar
 * 			Remove todos os itens da fila
 * @param:		Fila
 * @param:		Funcao que destroi um item da fila
 * @retorna:		(vazio)
 *---------------------------------------------------------------------------*/ 
void TFila_Limpar(TFila* Fila, TFuncaoDestruir FuncaoDestruir);

/* ----------------------------------------------------------------------------
 * funcao:		TFila_Tamanho
 * 			Retorna o quantidade de itens da fila
 * @param:		Fila
 * @retorna:		Inteiro com o tamanho
 *---------------------------------------------------------------------------*/ 
size_t TFila_Tamanho(TFila* Fila);

#endif
