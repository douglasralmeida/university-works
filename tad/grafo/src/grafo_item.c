/*
**	TIPO ABASTRATO DE DADOS GRAFO
**	DOUGLAS RODRIGUES DE ALMEIDA
**
**	Implementação dos componentes do grafo
**	
**/

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include "core.h"
#include "grafo_item.h"

/* Estrutura de uma aresta do grafo */
TGrafoAresta* TGrafoAresta_Criar(TGrafoVertice Vertice, TGrafoPeso Peso)
{
	TGrafoAresta* NovaAresta;
	
	NovaAresta = (TGrafoAresta*)malloc(sizeof(TGrafoAresta));
	if (NovaAresta == NULL)
	{
		printf("Erro (0x53). Erro ao alocar memoria.\n");
		return NULL;
	}
	NovaAresta->Destino = Vertice;
	NovaAresta->Peso = Peso;
	
	return NovaAresta;
}

void TGrafoAresta_Destruir(void** PAresta)
{
	free(*PAresta);
	*PAresta = NULL;
}

bool TGrafoAresta_Igual(void* Dado1, void* Dado2)
{
	TGrafoAresta* Aresta1;
	TGrafoAresta* Aresta2;
	
	Aresta1 = (TGrafoAresta*)Dado1;
	Aresta2 = (TGrafoAresta*)Dado2;
	return (Aresta1->Destino == Aresta2->Destino);
}

void TGrafoAresta_Imprimir(void* Dado)
{
	TGrafoAresta* Aresta;
	
	Aresta = (TGrafoAresta*)Dado;
	printf(" %2d [%d]", (int)Aresta->Destino, (int)Aresta->Peso);
}

/* Estrutura do caminhamento pelo grafo */
TGrafoCaminhoItem* TGrafoCaminhoItem_Criar(TGrafoVertice Vertice)
{
	TGrafoCaminhoItem* NovoCaminhoItem;
	
	NovoCaminhoItem = (TGrafoCaminhoItem*)malloc(sizeof(TGrafoCaminhoItem));
	if (NovoCaminhoItem == NULL)
	{
		printf("Erro (0x54). Erro ao alocar memoria.\n");
		return NULL;
	}
	NovoCaminhoItem->Antecessor = 0;
	NovoCaminhoItem->Distancia = INT_MAX;
	NovoCaminhoItem->JaVisitado = false;
	NovoCaminhoItem->Vertice = Vertice;
	
	return NovoCaminhoItem;
}

void TGrafoCaminhoItem_Destruir(void** PCaminhoItem)
{
	free(*PCaminhoItem);
	*PCaminhoItem = NULL;
}

bool TGrafoCaminhoItem_Comparar(void* Dado1, void* Dado2)
{
	TGrafoCaminhoItem* Item1;
	TGrafoCaminhoItem* Item2;
	
	Item1 = (TGrafoCaminhoItem*)Dado1;
	Item2 = (TGrafoCaminhoItem*)Dado2;
	return (Item1->Distancia > Item2->Distancia);
}
