/*
**	TIPO ABASTRATO DE DADOS GRAFO
**	DOUGLAS RODRIGUES DE ALMEIDA
**
**	Cabecalho e estruturas de para os componentes do grafo
**	
**/

#ifndef GRAFO_ITEM_H
#define GRAFO_ITEM_H

#include <stdio.h>
#include <stdlib.h>
#include "core.h"

/* Estrutura das vertice do grafo */
typedef size_t TGrafoVertice;

typedef unsigned int TGrafoPeso;

/* Estrutura das arestas do grafo */
typedef struct _TGrafoAresta {
	TGrafoVertice Destino;
	TGrafoPeso Peso;
} TGrafoAresta;

/* Estrutura do item de um caminho */
typedef struct _TGrafoCaminhoItem {
	unsigned int Distancia; //distancia de um vertice determinado ate o vertice atual
	TGrafoVertice Antecessor; //vertice antecessor do caminho
} TGrafoCaminhoItem;

TGrafoAresta* TGrafoAresta_Criar(TGrafoVertice Vertice, TGrafoPeso Peso);

void TGrafoAresta_Destruir(void** PAresta);

bool TGrafoAresta_CompararPeso(void* Dado1, void* Dado2);

bool TGrafoAresta_Igual(void* Dado1, void* Dado2);

void TGrafoAresta_Imprimir(void* Dado);

#endif
