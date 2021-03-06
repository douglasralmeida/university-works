/*
 *	TIPO ABSTRATO DE DADOS MATRIZ
 *	DOUGLAS RODRIGUES DE ALMEIDA
 *
 *	Cabeçalhos e estruturas de uma matriz esparsa usando ponteiros
 */

#ifndef MATRIZ_H
#define MATRIZ_H

#include "boolutils.h"
#include "core.h"

typedef struct TMatrizItem;

/* Estrutura da matriz */
typedef struct _TMatriz {
	size_t Colunas;		/*-- Nº de colunas da matriz --*/
	size_t Linhas;		/*-- Nº de linhas --*/
	TMatrizItem Frente;	/*-- Conteúdo da matriz --*/
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

TMatriz* TMatriz_Adicionar(TMatriz* MatrizA, TMatriz* MatrizB);

void TMatriz_Imprimir(TMatriz* Matriz);

TMatriz* TMatriz_Multiplicar(TMatriz* MatrizA, TMatriz* MatrizB);

TMatriz* TMatriz_Subtrair(TMatriz* MatrizA, TMatriz* MatrizB);
#endif
