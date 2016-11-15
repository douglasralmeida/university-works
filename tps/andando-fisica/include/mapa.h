/*
**	ANDANDO NA FÍSICA
**	DOUGLAS RODRIGUES DE ALMEIDA
**
**	Mapa
*/
#ifndef MAPA_H
#define MAPA_H

#include "boolutils.h"
#include "filaprior.h"
#include "list.h"
#include "grafo.h"

typedef char TMapaChave;

typedef size_t TMapaPos;

typedef struct _TMapaCaminho {
	TMapaChave Chave;
	TGrafoVertice LocalChave;
} TMapaCaminho;

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
	char* Bolso;
	unsigned short CapacidadeChaves;
	TLista* Chaves;
	TGrafo* Grafo;
	TGrafoVertice PontoInicial;
	TGrafoVertice PontoFinal;
	unsigned short QuantidadeChaves;
	bool TemSaida;
	size_t CustoCaminhamento;
	size_t CustoFinal;
} TMapa;

TMapaCaminho* TMapaCaminho_Criar(TMapaChave Chave, TGrafoVertice Vertice);

void TMapaCaminho_Destruir(void** PCaminho);

TMapaInfo* TMapaInfo_Criar(TMapaPos PosicaoX, TMapaPos PosicaoY);

void TMapaInfo_Destruir(void** PInfo); 

TMapa* TMapa_Criar(void);

void TMapa_Destruir(TMapa** PMapa);

void TMapa_CaminharComChaves(TMapa* Mapa);

TGrafoPeso TMapa_CaminhamentoCusto(TGrafo* Grafo, TGrafoVertice Vertice);

void TMapa_EncontrarMenorCaminho(TMapa* Mapa);

void TMapa_ImprimirResultado(TMapa* Mapa);

void TMapa_InserirCaminho(TMapa* Mapa, TGrafoVertice Origem, TGrafoVertice Destino);

void TMapa_ProcessarLinha(TMapa* Mapa, char* Linha, int PosicaoX, int TamanhoLinha, int Altura);

bool TMapa_ProcessarEntrada(TMapa* Mapa);

#endif
