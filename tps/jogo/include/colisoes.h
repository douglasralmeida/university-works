#ifndef _COLISOES_H_
#define _COLISOES_H_

#include <stdio.h>
#include "matematica.h"
#include "tipos.h"

typedef struct {
	TPonto* Vertices;
	unsigned int VerticesCont;
} TMascara;

typedef struct {
	TMascara* Mascaras;
	unsigned int MascarasCont;
	unsigned int MascaraProxPos;
} TColisor;

void MascaraDefinir(TMascara* Mascara, int NumVertices);
void MascaraLimpar(TMascara* Mascara);
void MascarasDesenhar(TColisor* Colisor, TPonto* PontoVisao);

int PoligonosSobreposicao(TMascara* MascaraA, TMascara* MascaraB);

TColisor* ColisorCriar(int Capacidade);
void ColisorDestruir(TColisor** PColisor);
int ColisorMascaraAdic(TColisor* Colisor, int NumVertices);
void ColisorMascaraRemover(TColisor* Colisor, int MascaraID);
int HaColisaoObjetos(TColisor* Colisor, unsigned int MascaraID);
int HaColisaoLimites(TMascara* Mascara, TPonto* PontoVisao);
int HaColisaoProjetil(TColisor* Colisor, unsigned int AtiradorID, TPonto* Inicio, TPonto* Fim);

#endif
