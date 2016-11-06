/*
**	ANDANDO NA FÍSICA
**	DOUGLAS RODRIGUES DE ALMEIDA
**
**	Algoritmo A*
*/
#ifndef GRAFO_CAMINHAMENTO_H
#define GRAFO_CAMINHAMENTO_H

#include "boolutils.h"
#include "grafo.h"

typedef TGrafoPeso (*TFuncaoHeuristica)(TGrafo* Grafo, TGrafoVertice VerticeAtual, TGrafoVertice VerticeDestino);

typedef struct _TVerticeDistancia {
	size_t Valor;
	TGrafoVertice Origem;
} TVerticeDistancia;

TVerticeDistancia* TVerticeDistancia_Criar(TGrafoVertice Vertice, size_t Valor);

void TVerticeDistancia_Destruir(void** PDistancia);

bool TVerticeDistancia_Comparar(void* Distancia1, void* Distancia2);

bool TGrafo_MenorCaminho(TGrafo* Grafo, TGrafoVertice Inicio, TGrafoVertice Final, TFuncaoHeuristica FuncaoHeuristica);

#endif
