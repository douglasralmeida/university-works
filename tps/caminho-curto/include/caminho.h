#ifndef CAMINHO_H
#define CAMINHO_H

#define "boolutils.h"

typedef struct TCaminho_ {
	int Origem;
	int Destino;
	int TempoMedio;
	bool Visitado;
} TCaminho;


TCaminho* TCaminho_Criar(int Origem, int Destino, int TempoMedio);

void TCaminho_Destruir(void** PCaminho);

bool TCaminho_Comparar(void* PCaminho1, void* PCaminho2);
#endif
