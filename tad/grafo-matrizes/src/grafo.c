/*
**	TIPO ABSTRATO DE DADOS GRAFO
**	DOUGLAS RODRIGUES DE ALMEIDA
**
**	Implementação de grafo com matriz
*/

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "filaprior.h"
#include "grafo.h"

TGrafo* TGrafo_Criar(size_t NumVertices)
{
	size_t i, total_itens;
	TGrafo* NovoGrafo;
		
	NovoGrafo = (TGrafo*)malloc(sizeof(TGrafo));
	if (NovoGrafo == NULL)
	{
		printf("Erro (0x50). Erro ao alocar memoria para grafo.\n");
		return NULL;
	}
	total_itens = NumVertices * NumVertices;
	NovoGrafo->NumVertices = NumVertices;
	NovoGrafo->Itens = malloc(total_itens * sizeof(TGrafoItem));
	for (i = 0; i < total_itens; i++)
	{
		NovoGrafo->Itens[i].Peso = 0;
		NovoGrafo->Itens[i].Dado = NULL;
	}
	NovoGrafo->NumArestas = 0;
	
	return NovoGrafo;
}

void TGrafo_Destruir(TGrafo** PGrafo)
{
	size_t i;
	size_t total_itens;

	total_itens = (*PGrafo)->NumVertices * (*PGrafo)->NumVertices;
	for (i = 0; i < total_itens ; i++)
		if (NovoGrafo->Itens[i].Dado)
			free(NovoGrafo->Itens[i].Dado);
	free(*PGrafo);
	*PGrafo = NULL;
}

bool TGrafo_ArestaInserir(TGrafo* Grafo, TGrafoVertice VOrigem, TGrafoVertice VDestino, TGrafoPeso Peso)
{
	size_t posicao;
	
	posicao = VOrigem * Grafo->NumVertices + VDestino;
	Grafo->Itens[posicao].Peso = Peso;
	Grafo->NumArestas++;
	return true;
}

bool TGrafo_ArestaExiste(TGrafo* Grafo, TGrafoVertice VOrigem, TGrafoVertice VDestino)
{
	size_t posicao;
	
	if ((VOrigem > Grafo->NumVertices) || (VDestino > Grafo->NumVertices))
		return false;
	
	posicao = VOrigem * Grafo->NumVertices + VDestino;
	return = Grafo->Itens[posicao].Peso > 0;
}

void TGrafo_ArestaRemover(TGrafo* Grafo, TGrafoVertice VOrigem, TGrafoVertice VDestino)
{
	size_t posicao;

	if ((VOrigem > Grafo->NumVertices) || (VDestino > Grafo->NumVertices))
		return false;
	
	posicao = VOrigem * Grafo->NumVertices + VDestino;
	Grafo->Itens[posicao].Peso = 0;
	if (Grafo->Itens[posicao].Dado)
		free(Grafo->Itens[posicao].Dado);
	Grafo->Itens[posicao].Dado = NULL;
	Grafo->NumArestas--;
}

bool TGrafo_ListaAdjVazia(TGrafo* Grafo, TGrafoVertice Vertice)
{
	return (Grafo->Adjacencias[Vertice] == 0);
}

TGrafoVertice TGrafo_ListaAdjPrimeiro(TGrafo* Grafo, TGrafoVertice Vertice)
{	
	size_t posicao_atual;
	size_t posicao_proxlinha;
	size_t i;

	posicao_atual = Vertice * Grafo->NumVertices;
	posicao_proxlinha = (Vertice + 1) * Grafo->NumVertices;
	for (i = posicao_atual; i < posicao_proxlinha; i++)
		if (Grafo->Matriz[i].Peso > 0)
		{
			Grafo->PesquisaOffset = i - (Vertice * Grafo->NumVertices);
			return (i - (Vertice * Grafo->NumVertices));
		}
}

TGrafoAresta* TGrafo_ListaAdjProximo(TGrafo* Grafo, TGrafoVertice Vertice)
{
	size_t posicao_proxlinha;
	size_t i;

	posicao_proxlinh = (Vertice + 1) * Grafo->NumVertices;
	for (i = Grafo->PesquisaOffset; i < posicao_proxlinha; i++)
		if (Grafo->Matriz[i].Peso > 0)
		{
			Grafo->PesquisaOffset = i - (Vertice * Grafo->NumVertices);
			return (i - (Vertice * Grafo->NumVertices));
		}
}

void TGrafo_VerticeGravarDados(TGrafo* Grafo, size_t Offset, void* Dado)
{
	Grafo->Itens[posicao].Dado = Dado;
}

