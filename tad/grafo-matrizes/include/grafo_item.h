/*
**	TIPO ABASTRATO DE DADOS GRAFO
**	DOUGLAS RODRIGUES DE ALMEIDA
**
**	Cabeçalho e estruturas para os componentes do grafo
**	
**/

#ifndef GRAFO_ITEM_H
#define GRAFO_ITEM_H

#include <stdio.h>
#include <stdlib.h>
#include "core.h"

/* Estrutura do peso dos vertices do grafo */
typedef unsigned long TGrafoPeso;

/* Estrutura dos vertices do grafo */
typedef unsigned long TGrafoVertice;

/* Estrutura dos items da matriz que representa grafo */
typedef struct _TGrafoItem {
	TGrafoPeso Peso;
	void* Dado;
} TGrafoItem;

/* Estrutura do item de um caminho */
typedef struct _TGrafoCaminhoItem {
	TGrafoVertice Antecessor; 	/*vertice antecessor do caminho*/
	int Distancia; 			/*distancia de um vertice determinado ate o vertice atual*/
	bool JaVisitado; 		/*grava a visita durante o caminhamento*/
	TGrafoVertice Vertice; 		/*vertice do item*/
} TGrafoCaminhoItem;

/* ----------------------------------------------------------------------------
 * funcao:		TGrafoAresta_Criar
 * 			Cria uma aresta
 * @param:		Vertice de destino da aresta
 * @param:		Peso da aresta
 * @retorna:		A aresta alocada
 *---------------------------------------------------------------------------*/
TGrafoItem* TGrafoItem_Criar(void* Dado, TGrafoPeso Peso);

/* ----------------------------------------------------------------------------
 * funcao:		TGrafoAresta_Destruir
 * 			Destrói uma aresta
 * @param:		Aresta
 * @retorna:		(vazio)
 *---------------------------------------------------------------------------*/
void TGrafoItem_Destruir(void** PItem);

/* ----------------------------------------------------------------------------
 * funcao:		TGrafoCaminho_Criar
 * 			Cria um item do caminhamento do grafo
 * @param:		Vertice de destino do caminhamento até este item
 * @retorna:		O item do caminho alocado
 *---------------------------------------------------------------------------*/
TGrafoCaminhoItem* TGrafoCaminhoItem_Criar(TGrafoVertice Vertice);

/* ----------------------------------------------------------------------------
 * funcao:		TGrafoCaminhoItem_Destruir
 * 			Destróio o item do caminhamento do grafo
 * @param:		Item do caminhamento do grafo
 * @retorna:		(vazio)
 *---------------------------------------------------------------------------*/
void TGrafoCaminhoItem_Destruir(void** PCaminhoItem);

/* ----------------------------------------------------------------------------
 * funcao:		TGrafoCaminhoItem_Comparar
 * 			Compara a distância entre dois itens do caminhamento e suas origens
 * @param:		Item do caminhamento do grafo
 * @param:		Outro item do caminhamento do grafo
 * @retorna:		True, se o primeiro item tem distância maior, false caso contrário
 *---------------------------------------------------------------------------*/
bool TGrafoCaminhoItem_Comparar(void* Dado1, void* Dado2);

#endif
