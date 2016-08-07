/*
 *	TIPO ABSTRATO DE DADOS MATRIZ
 *	DOUGLAS RODRIGUES DE ALMEIDA
 *
 *	Implementação de uma matriz com vetores
 */

#include "matriz.h"

TMatriz* TMatriz_Criar(size_t NumLinhas, size_t NumColunas)
{
	int i, j;
	TMatriz* NovaMatriz;

	NovaMatriz = malloc(sizeof(TMatriz));
	if (NovaMatriz == NULL)
	{
		printf("Erro (0x61): Erro ao alocar matriz.\n");
		return NULL;
	}
	NovaMatriz->Itens = malloc(NumLinhas * sizeof(TMatrizItem*);
	if (NovaMatriz->Itens == NULL)
	{
		printf("Erro (0x62): Erro ao alocar linhas da matriz.\n");
		free(NovaMatriz);
		return NULL;
	}
	for (i = 0; i < NumLinhas; i++)
	{
		NovaMatriz->Itens[i] = malloc(NumColunas * sizeof(TMatrizItem));
		if (NovaMatriz->Itens[i] == NULL)
		{
			printf("Erro (0x63): Erro ao alocar colunas da matriz.\n");
			for (j = 0; j < i; j++)
				free(NovaMatriz->Itens[j]);
			free(NovaMatriz->Itens);
			free(NovaMatriz);
		}
	}
	
	return NovaMatriz;
}

void TMatriz_Destruir(TMatriz** PMatriz)
{
	int i;

	if (PMatriz != NULL)
	{
		for (i = 0; i < (*PMatriz)->NumLinhas; i++)
			free((*PMatriz)->Itens[i]);
		free((*PMatriz)->Itens);
		free(*PMatriz);
		*PMatriz = NULL;
	}
}

TMatriz* TMatriz_Adicionar(TMatriz* MatrizA, TMatriz* MatrizB)
{
	int i, j;
	TMatriz* MatrizR;

	if (MatrizA->Linhas != MatrizB->Linhas)
	{
		printf("Erro (0x64). As matrizes a serem somadas devem ter o numero de linhas igual.\n");
		return NULL;
	}
	if (MatrizA->Colunas != MatrizB->Colunas)
	{
		printf("Erro (0x65). As matrizes a serem somadas devem ter o numero de colunas igual.\n");
		return NULL;
	}
	MatrizR = TMatriz_Criar(MatrizA->Linhas, MatrizA->Colunas);
	if (MatrizR == NULL)
		return NULL;
	for (i = 0; i < MatrizA->NumLinhas); i++)
		for (j = 0; j < MatrizA->NumColunas; j++)
			MatrizR->Itens[i][j] = MatrizA->Itens[i][j] + MatrizB->Itens[i][j];

	return MatrizR;
}

TMatriz* TMatriz_Multiplicar(TMatriz* MatrizA, TMatriz* MatrizB)
{
	int i, j, k;
	TMatriz* MatrizR;
	TMatrizItem Soma;

	if (MatrizA->Colunas != MatrizB->Linhas)
	{
		printf("Erro (0x68). O numero de colunas da primeira matriz deve ser igual o numero de linhas da segunda matriz.\n");
		return NULL;
	}
	MatrizR = TMatriz_Criar(MatrizA->Linhas, MatrizB->Colunas);
	if (MatrizR == NULL)
		return NULL;
	for (i = 0; i < MatrizA->NumLinhas); i++)
		for (j = 0; j < MatrizA->NumColunas; j++)
		{
			Soma = 0;
		}

	return MatrizR;	
}

TMatriz* TMatriz_Subtrair(TMatriz* MatrizA, TMatriz* MatrizB)
{
	int i, j;
	TMatriz* MatrizR;

	if (MatrizA->Linhas != MatrizB->Linhas)
	{
		printf("Erro (0x66). As matrizes a serem subtraidas devem ter o numero de linhas igual.\n");
		return NULL;
	}
	if (MatrizA->Colunas != MatrizB->Colunas)
	{
		printf("Erro (0x67). As matrizes a serem subtraidas devem ter o numero de colunas igual.\n");
		return NULL;
	}
	MatrizR = TMatriz_Criar(MatrizA->Linhas, MatrizA->Colunas);
	if (MatrizR == NULL)
		return NULL;
	for (i = 0; i < MatrizA->NumLinhas); i++)
		for (j = 0; j < MatrizA->NumColunas; j++)
			MatrizR->Itens[i][j] = MatrizA->Itens[i][j] - MatrizB->Itens[i][j];

	return MatrizR;
}
