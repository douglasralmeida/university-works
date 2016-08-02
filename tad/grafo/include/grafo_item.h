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
	int Distancia; 				/*distancia de um vertice determinado ate o vertice atual*/
	bool JaVisitado; 			/*grava a visita durante o caminhamento*/
	TGrafoVertice Vertice; 		/*vertice do item*/
} TGrafoCaminhoItem;

TGrafoAresta* TGrafoAresta_Criar(TGrafoVertice Vertice, TGrafoPeso Peso);

void TGrafoAresta_Destruir(void** PAresta);

bool TGrafoAresta_Igual(void* Dado1, void* Dado2);

void TGrafoAresta_Imprimir(void* Dado);

TGrafoCaminhoItem* TGrafoCaminhoItem_Criar(TGrafoVertice Vertice);

void TGrafoCaminhoItem_Destruir(void** PCaminhoItem);

bool TGrafoCaminhoItem_Comparar(void* Dado1, void* Dado2);

#endif