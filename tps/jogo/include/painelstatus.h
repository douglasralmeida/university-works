#ifndef _PAINELSTATUS_H_
#define _PAINELSTATUS_H_

#include <allegro5/allegro.h>

typedef struct {
	ALLEGRO_BITMAP* CoracaoVermelho;
	ALLEGRO_BITMAP* CoracaoCinza;
	ALLEGRO_BITMAP* Face;
	int FaseID;
	int MaxSangue;
	int Sangue;
} TPainelStatus;

TPainelStatus* PainelStatusCriar(void);
void PainelStatusDestruir(TPainelStatus** PainelStatus);
void PainelStatusExibir(TPainelStatus* PStatus);

#endif