/*
**	ANDANDO NA FÍSICA
**	DOUGLAS RODRIGUES DE ALMEIDA
**
**	Algoritmo A*
*/
#ifndef MAPA_CAMINHAMENTO_H
#define MAPA_CAMINHAMENTO_H

#include "boolutils.h"
#include "grafo.h"
#include "mapa.h"

typedef TGrafoPeso (*TFuncaoHeuristica)(TGrafo* Grafo, TGrafoVertice VerticeAtual, TGrafoVertice VerticeDestino);

typedef struct _TVerticeDistancia {
	size_t Valor;
	TGrafoVertice Origem;
} TVerticeDistancia;

TVerticeDistancia* TVerticeDistancia_Criar(TGrafoVertice Vertice, size_t Valor);

void TVerticeDistancia_Destruir(void** PDistancia);

bool TVerticeDistancia_Comparar(void* Distancia1, void* Distancia2);

bool TMapa_CaminhoEBuracoNegro(TGrafo* Grafo, TGrafoVertice Vertice, TGrafoVertice* Destino);

TGrafoPeso TMapa_CaminhamentoHeuristica(TMapa* Mapa, TGrafoVertice VerticeAtual, TGrafoVertice VerticeDestino);

bool TMapa_MenorCaminho(TMapa* Mapa);

#endif
