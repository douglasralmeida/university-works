/*
**	ANDANDO NA FÍSICA
**	DOUGLAS RODRIGUES DE ALMEIDA
**
**	Mapa
*/
#ifndef MAPA_H
#define MAPA_H

typedef struct _TMapaItem {
	char ID;
	int DestinoH;
	int DestinoV;	
} TMapaItem;

void TMapa_ProcessarLinha(char* Linha, int Tamanho);

bool TMapa_ProcessarEntrada(void);

#endif
