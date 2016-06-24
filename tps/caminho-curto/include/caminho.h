#ifndef CAMINHO_H
#define CAMINHO_H

#include "boolutils.h"

typedef struct TCaminho_ {
	unsigned int Origem;
	unsigned int Destino;
	unsigned int TempoMedio;
} TCaminho;


TCaminho* TCaminho_Criar(unsigned int Origem, unsigned int Destino, unsigned int TempoMedio);

void TCaminho_Destruir(void** PCaminho);

bool TCaminho_Comparar(void* PCaminho1, void* PCaminho2);
#endif
