/*
**	ANDANDO NA FÍSICA
**	DOUGLAS RODRIGUES DE ALMEIDA
**
**	Mapa
*/
#include <stdio.h>
#include <stdlib.h>
#include "mapa.h"

void TMapa_ProcessarLinha(TMapa* Mapa, char* String, int Linha, int Tamanho)
{
	int i;
	char s[3];
	size_t posicao;
	TMapaItem* Item;

	for (i = 0; i < Tamanho; i++)
	{
		sscanf(String, "%s", s);
		Item = malloc(sizeof(TMapaItem));
		Item->DestinoH = 0;
		Item->DestinoV = 0;
		Item->ID = s[0];
		if (s[0] >= '0' && s[0] <= '9')
		{
			Item->ID = 'B';
			Item->DestinoH = s[0];
			Item->DestinoV = s[1];
		} else
		{
			switch (s[0])
			{
				case 'V':
					Mapa->PontoInicial[0] = Linha;
					Mapa->PontoInicial[1] = i;
				break;

				case 'E':
					Mapa->PontoFinal[0] = Linha;
					Mapa->PontoFinal[1] = i;
				break;
			}
		}
		posicao = Linha * Mapa->Grafo->NumVertices + i;
		TGrafo_VerticeGravarDados(Mapa->Grafo, posicao, Item);
	}
}

bool TMapa_ProcessarEntrada(TMapa* Mapa)
{
	int i;
	int altura, largura, capacidade_chaves;
	char linha[20];

	scanf("%d %d %d", &altura, &largura, &capacidade_chaves);
	for (i = 0; i < altura; i++)
	{
		scanf("%s", linha);
		TMapa_ProcessarLinha(Mapa, linha, i, 9);
	}

	return true;
}

void TMapa_ConstruirAresta(TGrafo* Grafo, TGrafoVertice A, TGrafoVertice B)
{
	
}

void TMapa_ConstruirGrafo(TMapa* Mapa)
{
	TGrafoVertice i;

	for (i = 0; i < Mapa->Grafo->NumVertices; i++)
	{
		for (j = 0; j < Mapa->Grafo->NumVertices; j++)
		{
			
		}
		if (i % Mapa->Grafo->NumVertices != 0)
			TMapa_ConstruirAresta(Mapa->Grafo, i, i - 1);
		else if (i % Mapa->Grafo->NumVertices != Mapa->Grafo->NumVertices - 1)
			TMapa_ConstruirAresta(Mapa->Grafo, i, i + 1);
		if (i / Mapa->Grafo->NumVertices != 0)
			TMapa_ConstruirAresta(Mapa->Grafo, i, i - Mapa->Grafo->NumVertices);
		else (i / Mapa->Grafo->NumVertices != v - 1)
			TMapa_ConstruirAresta(Mapa->Grafo, i, i + Mapa->Grafo->NumVertices):
	}
}
