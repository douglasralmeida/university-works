#ifndef CAMINHO_H
#define CAMINHO_H

typedef struct TCaminho_ {
	int Origem;
	int Destino;
	int TempoMedio;
} TCaminho;


TCaminho* TCaminho_Criar(int Origem, int Destino, int TempoMedio);

void TCaminho_Destruir(void** PCaminho);

bool TCaminho_Comparar(void* PCaminho1, void* PCaminho2);
#endif
