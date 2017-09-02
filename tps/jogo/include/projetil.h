#ifndef _PROJETIL_H_
#define _PROJETIL_H_

#include "fisica.h"
#include "matematica.h"

typedef enum {pmCrescendo, pmEstavel, pmDiminuindo} TProjetilModo;

typedef struct {
	int ID;
	int AtiradorID;
	int Comprimento;
	int EstaVivo;
	int EFuncional;
	TProjetilModo Modo;
	TPonto PontoPartida;
	TPonto PontoDestino;
	TPonto PosAnterior;
	TPonto Inicio;
	TPonto Fim;
	TVetor Trajetoria;
} TProjetil;

typedef struct {
	int QuantProjetil;
	TProjetil** Projetil;
} TProjetis;

TProjetil* ProjetilCriar(TPonto PosicaoInicial);
void ProjetilDestruir(TProjetil** PProjetil);
void ProjetilDesenhar(TProjetil* Projetil, TPonto* PontoVisao);
int ProjetilMovimentar(TProjetil* Projetil);
void ProjetilPosicionar(TProjetil* Projetil);
#endif