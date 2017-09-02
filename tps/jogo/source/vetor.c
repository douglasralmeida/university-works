#include <stdlib.h>
#include <string.h>
#include "vetor.h"

void VetorDestruir(void** PVetor)
{
	free(*PVetor);
	*PVetor = NULL;
}

void MatrizDestruir(void*** PMatriz, int Linhas)
{
	int i;
	for (i = 0; i < Linhas; i++)
	{
		VetorDestruir(*PMatriz + i);
	}
	free(*PMatriz);
	*PMatriz = NULL;
}

char** CMatrizCriar(int x, int y)
{
	int i;
	char** AMatriz;
	AMatriz = (char**)malloc(x * sizeof(char*));
	for (i = 0; i < x; i++)
		AMatriz[i] = CVetorCriar(y);
	return AMatriz;
}

char* CVetorCriar(int Tamanho)
{
	char* AVetor;
	AVetor = (char*)malloc(Tamanho * sizeof(char));
	strcpy(AVetor, "");
	return AVetor;
}

int** IMatrizCriar(int x, int y)
{
	int i;
	int** AMatriz;
	
	AMatriz = (int**)malloc(x * sizeof(int*));
	for (i = 0; i < x; i++)
		AMatriz[i] = (int*)malloc(y * sizeof(int));
	
	return AMatriz;
}

int* IVetorCriar(int Tamanho)
{
	int* AVetor;
	
	AVetor = (int*)	malloc(Tamanho * sizeof(int));
	
	return AVetor;
}

int IVetorPos(int* Array, int n, int x)
{
	int i;
	int result = -1;
	
	for (i = 0; i < n; i++)
	{
		if (Array[i] == x)
			return i;
	}
	
	return result;
}

TPonto** PMatrizCriar(int x, int y)
{
	int i;
	TPonto** AMatriz;
	
	AMatriz = (TPonto**)malloc(x * sizeof(TPonto*));
	for (i = 0; i < x; i++)
		AMatriz[i] = (TPonto*)malloc(y * sizeof(TPonto));

	return AMatriz;
}