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

/* Estrutura dos vertices do grafo */
typedef size_t TGrafoVertice;

/* Estrutura do peso dos vertices do grafo */
typedef unsigned int TGrafoPeso;

/* Estrutura das arestas do grafo */
typedef struct _TGrafoAresta {
	TGrafoVertice Destino;
	TGrafoPeso Peso;
} TGrafoAresta;

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
TGrafoAresta* TGrafoAresta_Criar(TGrafoVertice Vertice, TGrafoPeso Peso);

/* ----------------------------------------------------------------------------
 * funcao:		TGrafoAresta_Destruir
 * 			Destrói uma aresta
 * @param:		Aresta
 * @retorna:		(vazio)
 *---------------------------------------------------------------------------*/
void TGrafoAresta_Destruir(void** PAresta);

/* ----------------------------------------------------------------------------
 * funcao:		TGrafoAresta_Igual
 * 			Checa se duas arestas são iguais
 * @param:		Aresta a ser comparada
 * @param:		Outra aresta a ser comparada
 * @retorna:		True se ambas forem iguais. False, caso contrário
 *---------------------------------------------------------------------------*/
bool TGrafoAresta_Igual(void* Dado1, void* Dado2);

/* ----------------------------------------------------------------------------
 * funcao:		TGrafoAresta_Imprimir
 * 			Imprimir uma aresta na tela
 * @param:		Aresta
 * @retorna:		(vazio)
 *---------------------------------------------------------------------------*/
void TGrafoAresta_Imprimir(void* Dado);

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
