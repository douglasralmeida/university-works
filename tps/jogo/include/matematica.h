#ifndef _MATEMATICA_H_
#define _MATEMATICA_H_

#include "tipos.h"

typedef struct {
	TPonto PontoInicial;
	TPonto PontoFinal;
} TQuadra;

typedef struct {
	TPonto Fim;
	TPonto Inicio;
} TReta;

typedef struct {
	float Norma;
	short Sentido;//-1 ou +1
	float Angulo;//0 a 180 graus em relacao ao eixo das abcissas
} TVetor;

float AnguloParaRadiano(float Angulo);
int ChecarLimites(TQuadra* Quadra, TPonto* PontoVisao);
float Determinante(float x1, float y1, float x2, float y2);
float Max(float x1, float x2);
float Min(float x1, float x2);
int ExisteSobreposicaoQuadraPonto(TQuadra* Quadra, TPonto* Ponto);
int ExisteSobreposicaoQuadraReta(TQuadra* Quadra, TReta* Reta);
int ExisteSobreposicaoQuadras(TQuadra* QuadraA, TQuadra* QuadraB);
int ExisteSobreposicaoRetas(TReta* RetaA, TReta* RetaB);
float ObjetoPontoDistancia(TPonto* Ponto, TPonto* Objeto, unsigned int NumVertices);
TPonto* PontoCriar(float x, float y);
void PontoRotacionar(TPonto* Ponto, TPonto* Centro, float Angulo);
float PontosDistancia(TPonto* PontoA, TPonto* PontoB);
float RadianoParaAngulo(float Rad_Angulo);
TPonto* RetasIntersecao(TReta* RetaA, TReta* RetaB);
float RetaPontoDistancia(TReta* Reta, TPonto* Ponto);
float SegmentoAngulo(TPonto* PontoInicial, TPonto* PontoFinal);
float SegmentoPontoDistancia(TPonto* PontoFinal, TPonto* PontoInicial, TPonto* PontoA);
void VetorInverter(TVetor* Vetor);
void VetorGirar90AH(TVetor* Vetor);
void VetorGirar90H(TVetor* Vetor);
TVetor* VetorDoisPontos(TPonto* PontoA, TPonto* PontoB);
#endif