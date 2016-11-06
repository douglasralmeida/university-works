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

typedef char TMapaChave;

typedef size_t TMapaPos;

typedef enum {
	mtBuracoNegro,
	mtCaminhavel,
	mtChave,
	mtFim,
	mtInicio,
	mtParede,
	mtPorta
} TMapaTipo;

typedef struct _TMapaInfo {
	TMapaPos PosicaoX;
	TMapaPos PosicaoY;
	TMapaTipo Tipo;
	TMapaChave Chave;
	TGrafoVertice DestinoBuraco;
	short Passou;
} TMapaInfo;

typedef struct _TMapa {
	short* PodeCaminhar;
	unsigned short CapacidadeChaves;
	TGrafo* Grafo;
	TGrafoVertice PontoInicial;
	TGrafoVertice PontoFinal;
	bool TemSaida;
	size_t CustoCaminhamento;
} TMapa;

TMapaInfo* TMapaInfo_Criar(TMapaPos PosicaoX, TMapaPos PosicaoY);

void TMapaInfo_Destruir(void** PInfo); 

TMapa* TMapa_Criar(void);

void TMapa_Destruir(TMapa** PMapa);

TGrafoPeso TMapa_CaminhamentoCusto(TGrafo* Grafo, TGrafoVertice Vertice);

void TMapa_EncontrarMenorCaminho(TMapa* Mapa);

void TMapa_ImprimirResultado(TMapa* Mapa);

void TMapa_InserirCaminho(TMapa* Mapa, TGrafoVertice Origem, TGrafoVertice Destino);

void TMapa_ProcessarLinha(TMapa* Mapa, char* Linha, int PosicaoX, int TamanhoLinha);

bool TMapa_ProcessarEntrada(TMapa* Mapa);

#endif
