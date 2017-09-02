#ifndef _VETOR_H_
#define _VETOR_H_

#include "tipos.h"

void VetorDestruir(void** PVetor);
void MatrizDestruir(void*** PMatriz, int Linhas);

char** CMatrizCriar(int x, int y);

char* CVetorCriar(int Tamanho);

int** IMatrizCriar(int x, int y);

int* IVetorCriar(int Tamanho);
int IVetorPos(int* Array, int n, int x);

TPonto** PMatrizCriar(int x, int y);
#endif