#ifndef _FASE_H_
#define _FASE_H_

#include "tipos.h"

typedef struct {
	char* ArquivoMapa;
	char* BitmapPeleChefao;
	char* BitmapPeleInimigo;
	char* BitmapPeleJogador;
	char* MusicaAmbiente;
	char* Prologo;
	int QuantInimigos;
	TPonto PosicaoChefao;
	TPonto PosicaoInicial;
	TPonto PosicaoFinal;
	TPonto** PosInimigo;
} TFase;

TFase* FaseCriar(void);
void FaseDestruir(TFase** PFase);
int FaseAbrir(TFase* Fase, char* ArquivoFase);
void FaseIniciar(TFase* Fase);
#endif