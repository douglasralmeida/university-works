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
	float Valor;
	TGrafoVertice Vertice;
} TVerticeDistancia;

TVerticeDistancia* TVerticeDistancia_Criar(TGrafoVertice Vertice, float Valor);

void TVerticeDistancia_Destruir(void** PDistancia);

bool TVerticeDistancia_Comparar(void* Distancia1, void* Distancia2);

bool TMapa_CaminhoEBuracoNegro(TGrafo* Grafo, TGrafoVertice Vertice, TGrafoVertice* Destino);

bool TMapa_CaminhoEstaBloqueado(TMapa* Mapa, TGrafoVertice Vertice);

float TMapa_CaminhamentoHeuristica(TMapa* Mapa, TGrafoVertice VerticeAtual, TGrafoVertice VerticeDestino);

bool TMapa_Caminhar(TMapa* Mapa, TGrafoVertice Origem, TGrafoVertice Destino);

#endif
