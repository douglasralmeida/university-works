/*
 *	TIPO ABASTRATO DE DADOS FILA
 *	DOUGLAS RODRIGUES DE ALMEIDA
 *
 *	Cabecalho e estruturas de uma fila
 *	
 */

#ifndef FILA_H
#define FILA_H

#include <stdio.h>
#include <stdlib.h>
#include "boolutils.h"
#include "item.h"

/* Estrutura do no da fila */
typedef struct _TFilaNo TFilaNo;

struct _TFilaNo {
	TItem Item;
	TFilaNo* Proximo;
};

/* Estrutura da fila */
typedef struct _TFila {
	TFilaNo* Frente;
	size_t Tamanho;
	TFilaNo* Tras;
} TFila;

/* ----------------------------------------------------------------------------
 * funcao:		TFila_Criar
 * 				Cria uma fila vazia
 * @param:		(vazio)
 * @retorna:	A fila alocada
 *---------------------------------------------------------------------------*/ 
TFila* TFila_Criar(void);

/* ----------------------------------------------------------------------------
 * funcao:		TFila_Destruir
 * 				Destroi a fila
 * @param:		Fila
 * @retorna:	(vazio)
 *---------------------------------------------------------------------------*/ 
void TFila_Destruir(TLista** PFila);

/* ----------------------------------------------------------------------------
 * funcao:		TFila_Desenfileirar
 * 				Remove e retorna o proximo item da fila
 * @param:		Fila
 * @retorna:	O item removido
 *---------------------------------------------------------------------------*/ 
TItem TFila_Desenfileirar(TFila* Fila);

/* ----------------------------------------------------------------------------
 * funcao:		TFila_Enfileirar
 * 				Insere um item no final da fila
 * @param:		Fila
 * @param:		Item a ser inserido
 * @retorna:	(vazio)
 *---------------------------------------------------------------------------*/ 
void TFila_Enfileirar(TFila* Fila, const TItem Item);

/* ----------------------------------------------------------------------------
 * funcao:		TFila_Imprimir
 * 				Imprime a fila na tela
 * @param:		Fila
 * @retorna:	(vazio)
 *---------------------------------------------------------------------------*/ 
void TFila_Imprimir(TFila* Fila);

/* ----------------------------------------------------------------------------
 * funcao:		TFila_Limpar
 * 				Remove todos os itens da fila
 * @param:		Fila
 * @retorna:	(vazio)
 *---------------------------------------------------------------------------*/ 
void TFila_Limpar(TFila* Fila);

/* ----------------------------------------------------------------------------
 * funcao:		TFila_Tamanho
 * 				Retorna o quantidade de itens da fila
 * @param:		Fila
 * @retorna:	Inteiro com o tamanho
 *---------------------------------------------------------------------------*/ 
size_t TFila_Tamanho(TFila* Fila);

#endif