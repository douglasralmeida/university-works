/*
**	ANDANDO NA FÍSICA
**	DOUGLAS RODRIGUES DE ALMEIDA
**
**	Mapa
*/
#ifndef MAPA_H
#define MAPA_H

#include "boolutils.h"
#include "grafo.h"

typedef struct _TMapa {
	short* PodeCaminhar;
	TGrafo* Grafo;
	TGrafoVertice PontoInicial;
	TGrafoVertice PontoFinal;
	int TempoMinimo;
} TMapa;

TMapa* TMapa_Criar(void);

void TMapa_Destruir(TMapa** PMapa);

void TMapa_EncontrarMenorCaminho(TMapa* Mapa);

void TMapa_ImprimirResultado(TMapa* Mapa);

void TMapa_InserirCaminho(TMapa* Mapa, TGrafoVertice Origem, TGrafoVertice Destino);

void TMapa_ProcessarLinha(TMapa* Mapa, char* Linha, int PosicaoX, int TamanhoLinha);

bool TMapa_ProcessarEntrada(TMapa* Mapa);

#endif
