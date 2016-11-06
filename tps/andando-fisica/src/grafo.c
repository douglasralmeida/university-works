/*
**	TIPO ABSTRATO DE DADOS GRAFO
**	DOUGLAS RODRIGUES DE ALMEIDA
**
**	Implementação de grafo com matriz
*/

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include "filaprior.h"
#include "grafo.h"

TGrafo* TGrafo_Criar(size_t NumVertices, bool Direcionado)
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
	NovoGrafo->Direcionado = Direcionado;
	NovoGrafo->NumVertices = NumVertices;
	NovoGrafo->Adjacencias = malloc(NumVertices * sizeof(size_t));
	if (!NovoGrafo->Adjacencias)
	{
		free(NovoGrafo);
		return NULL;
	}
	NovoGrafo->CustoCaminhamento = 0;
	NovoGrafo->Itens = malloc(total_itens * sizeof(TGrafoItem));
	for (i = 0; i < total_itens; i++)
	{
		NovoGrafo->Itens[i].Peso = 0;
		NovoGrafo->Itens[i].Dado = NULL;
	}
	for (i = 0; i < NumVertices; i++)
	{
		NovoGrafo->Adjacencias[i] = 0;
	}
	NovoGrafo->NumArestas = 0;
	NovoGrafo->PesquisaOffset = 0;
	
	return NovoGrafo;
}

void TGrafo_Destruir(TGrafo** PGrafo)
{
	size_t i;
	size_t total_itens;

	total_itens = (*PGrafo)->NumVertices * (*PGrafo)->NumVertices;
	for (i = 0; i < total_itens ; i++)
		if ((*PGrafo)->Itens[i].Dado)
			free((*PGrafo)->Itens[i].Dado);
	free((*PGrafo)->Adjacencias);
	free((*PGrafo)->Itens);
	free(*PGrafo);
	*PGrafo = NULL;
}

bool TGrafo_ArestaInserir(TGrafo* Grafo, TGrafoVertice VOrigem, TGrafoVertice VDestino, TGrafoPeso Peso)
{
	size_t posicao;

	if ((VOrigem >= Grafo->NumVertices) || (VDestino >= Grafo->NumVertices))
		return false;
	
	posicao = VOrigem * Grafo->NumVertices + VDestino;
	Grafo->Itens[posicao].Peso = Peso;
	Grafo->Adjacencias[VOrigem]++;
	Grafo->NumArestas++;
	if (!Grafo->Direcionado)
	{
		posicao = VDestino * Grafo->NumVertices + VOrigem;
		Grafo->Itens[posicao].Peso = Peso;
		Grafo->Adjacencias[VDestino]++;
		Grafo->NumArestas++;
	}
	return true;
}

bool TGrafo_ArestaExiste(TGrafo* Grafo, TGrafoVertice VOrigem, TGrafoVertice VDestino)
{
	size_t posicao;
	
	if ((VOrigem >= Grafo->NumVertices) || (VDestino >= Grafo->NumVertices))
		return false;
	
	posicao = VOrigem * Grafo->NumVertices + VDestino;
	return (Grafo->Itens[posicao].Peso > 0);
}

void TGrafo_ArestaRemover(TGrafo* Grafo, TGrafoVertice VOrigem, TGrafoVertice VDestino)
{
	size_t posicao;

	if ((VOrigem >= Grafo->NumVertices) || (VDestino >= Grafo->NumVertices))
		return;
	
	posicao = VOrigem * Grafo->NumVertices + VDestino;
	Grafo->Itens[posicao].Peso = 0;
	if (Grafo->Itens[posicao].Dado)
		free(Grafo->Itens[posicao].Dado);
	Grafo->Itens[posicao].Dado = NULL;
	Grafo->Adjacencias[VOrigem]--;
	Grafo->NumArestas--;
	if (!Grafo->Direcionado)
	{
		posicao = VDestino * Grafo->NumVertices + VOrigem;
		Grafo->Itens[posicao].Peso = 0;
		if (Grafo->Itens[posicao].Dado)
			free(Grafo->Itens[posicao].Dado);
		Grafo->Itens[posicao].Dado = NULL;
		Grafo->Adjacencias[VDestino]--;
		Grafo->NumArestas--;		
	}
}

void TGrafo_Imprimir(TGrafo* Grafo)
{
	TGrafoVertice i;
	TGrafoVertice temp;
	TGrafoPeso peso;

	for (i = 0; i < Grafo->NumVertices; i++)
	{
		printf("Vertice %2lu: ", i);
		if (!TGrafo_ListaAdjVazia(Grafo, i))
		{
			TGrafo_ListaAdjPrimeiro(Grafo, i, &temp, &peso);
			printf("(%lu, %lu) ", i, temp);
			while (TGrafo_ListaAdjProximo(Grafo, i, &temp, &peso))
				printf("(%lu, %lu) ", i, temp);
		}
		printf("\n");
	}
}

bool TGrafo_ListaAdjVazia(TGrafo* Grafo, TGrafoVertice Vertice)
{
	return (Grafo->Adjacencias[Vertice] == 0);
}

bool TGrafo_ListaAdjPrimeiro(TGrafo* Grafo, TGrafoVertice Vertice, TGrafoVertice* Adjacencia, TGrafoPeso* Peso)
{	
	size_t posicao_atual;
	size_t posicao_proxlinha;
	size_t i;

	posicao_atual = Vertice * Grafo->NumVertices;
	posicao_proxlinha = (Vertice + 1) * Grafo->NumVertices;
	for (i = posicao_atual; i < posicao_proxlinha; i++)
		if (Grafo->Itens[i].Peso > 0) 
		{
			Grafo->PesquisaOffset = i+1;
			*Adjacencia = i - (Vertice * Grafo->NumVertices);
			*Peso = Grafo->Itens[i].Peso;
			return true;
		}
	return false;
}

bool TGrafo_ListaAdjProximo(TGrafo* Grafo, TGrafoVertice Vertice, TGrafoVertice* Adjacencia, TGrafoPeso* Peso)
{
	size_t posicao_proxlinha;
	size_t i;

	posicao_proxlinha = (Vertice + 1) * Grafo->NumVertices;
	for (i = Grafo->PesquisaOffset; i < posicao_proxlinha; i++)
		if (Grafo->Itens[i].Peso > 0)
		{
			Grafo->PesquisaOffset = i+1;
			*Adjacencia = i - (Vertice * Grafo->NumVertices);
			*Peso = Grafo->Itens[i].Peso;
			return true;
		}
	return false;
}

void TGrafo_DefinirVertice(TGrafo* Grafo, TGrafoVertice Vertice, void* Dado)
{
	size_t posicao_atual;

	posicao_atual = Vertice * Grafo->NumVertices;
	Grafo->Itens[posicao_atual].Dado = Dado;
}

void* TGrafo_ObterVertice(TGrafo* Grafo, TGrafoVertice Vertice)
{
	size_t posicao_atual;

	posicao_atual = Vertice * Grafo->NumVertices;

	return Grafo->Itens[posicao_atual].Dado;	
}
