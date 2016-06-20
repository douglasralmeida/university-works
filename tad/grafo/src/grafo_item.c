/*
**	TIPO ABASTRATO DE DADOS GRAFO
**	DOUGLAS RODRIGUES DE ALMEIDA
**
**	Implementacao dos componentes do grafo
**	
**/

#include <stdio.h>
#include <stdlib.h>
#include "core.h"
#include "grafo_item.h"

/* Estrutura das vertice do grafo */
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
	PAresta = NULL;
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
