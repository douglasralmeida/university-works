/*
 *	TIPO ABSTRATO DE DADOS MATRIZ
 *	DOUGLAS RODRIGUES DE ALMEIDA
 *
 *	Cabeçalhos e estruturas de uma matriz com vetores
 */

#ifndef MATRIZ_H
#define MATRIZ_H

#include "boolutils.h"
#include "core.h"

typedef int TMatrizItem;

/* Estrutura da matriz */
typedef struct _TMatriz {
	size_t Colunas;		/*-- Nº de colunas da matriz --*/
	size_t Linhas;		/*-- Nº de linhas --*/
	TMatrizItem** Itens;		/*-- Conteúdo da matriz --*/
} TMatriz;

/* ----------------------------------------------------------------------------
 * funcao:		TMatriz_Criar
 * 			Cria uma matriz com zeros
 * @param:		Quantidade de linhas da matriz
 * @param:		Quantidade de colunas da matriz
 * @retorna:		A matriz alocada
 *---------------------------------------------------------------------------*/ 
TMatriz* TMatriz_Criar(size_t NumLinhas, size_t NumColunas);

void TMatriz_Destruir(TMatriz** PMatriz);

bool TMatriz_AlterarItem(TMatriz* Matriz, const size_t Linha, const size_t Coluna, const TMatrizItem Valor);

TMatriz* TMatriz_Adicionar(TMatriz* MatrizA, TMatriz* MatrizB);

void TMatriz_Imprimir(TMatriz* Matriz);

TMatriz* TMatriz_Multiplicar(TMatriz* MatrizA, TMatriz* MatrizB);

TMatriz* TMatriz_Subtrair(TMatriz* MatrizA, TMatriz* MatrizB);
#endif
