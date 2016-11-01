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
TGrafoItem* TGrafoItem_Criar(void* Dado, TGrafoPeso Peso)
{
	TGrafoItem* NovoItem;
	
	NovoItem = (TGrafoItem*)malloc(sizeof(TGrafoItem));
	if (NovoItem == NULL)
	{
		printf("Erro (0x53). Erro ao alocar memoria.\n");
		return NULL;
	}
	NovoItem->Dado = Dado;
	NovoItem->Peso = Peso;
	
	return NovoItem;
}

void TGrafoItem_Destruir(void** PItem)
{
	if (((TGrafoItem*) *PItem)->Dado)
		free(((TGrafoItem*)*PItem)->Dado);
	free(*PItem);
	*PItem = NULL;
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
