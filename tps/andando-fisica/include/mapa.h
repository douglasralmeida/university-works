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

typedef struct _TMapaItem {
	char ID;
	int DestinoH;
	int DestinoV;	
} TMapaItem;

typedef struct _TMapa {
	TGrafo* Grafo;
	TGrafoVertice PontoInicial[2];
	TGrafoVertice PontoFinal[2];
} TMapa;

void TMapa_ProcessarLinha(TMapa* Mapa, char* String, int Linha, int Tamanho);

bool TMapa_ProcessarEntrada(TMapa* Mapa);

void TMapa_ProcessarGrafo(TMapa* Mapa);

#endif
