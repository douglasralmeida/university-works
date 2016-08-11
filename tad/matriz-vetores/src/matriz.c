/*
 *	TIPO ABSTRATO DE DADOS MATRIZ
 *	DOUGLAS RODRIGUES DE ALMEIDA
 *
 *	Implementação de uma matriz com vetores
 */

#include <stdio.h>
#include <stdlib.h>
#include "matriz.h"

TMatriz* TMatriz_Criar(size_t NumLinhas, size_t NumColunas)
{
	size_t i, j;
	TMatriz* NovaMatriz;

	NovaMatriz = malloc(sizeof(TMatriz));
	if (NovaMatriz == NULL)
	{
		printf("Erro (0x61): Erro ao alocar matriz.\n");
		return NULL;
	}
	NovaMatriz->Itens = malloc(NumLinhas * sizeof(TMatrizItem*));
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
			return NULL;
		}
	}
	NovaMatriz->Linhas = NumLinhas;
	NovaMatriz->Colunas = NumColunas;
	return NovaMatriz;
}

void TMatriz_Destruir(TMatriz** PMatriz)
{
	size_t i;

	if (PMatriz != NULL)
	{
		for (i = 0; i < (*PMatriz)->Linhas; i++)
			free((*PMatriz)->Itens[i]);
		free((*PMatriz)->Itens);
		free(*PMatriz);
		*PMatriz = NULL;
	}
}

bool TMatriz_AlterarItem(TMatriz* Matriz, const size_t Linha, const size_t Coluna, const TMatrizItem Valor)
{
	if ((Linha <= Matriz->Linhas) && (Coluna <= Matriz->Colunas) && (Linha > 0) && (Coluna > 0))
	{
		Matriz->Itens[Linha-1][Coluna-1] = Valor;
		return true;
	}
	else
		return false;
}

TMatriz* TMatriz_Adicionar(TMatriz* MatrizA, TMatriz* MatrizB)
{
	size_t i, j;
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
	for (i = 0; i < MatrizA->Linhas; i++)
		for (j = 0; j < MatrizA->Colunas; j++)
			MatrizR->Itens[i][j] = MatrizA->Itens[i][j] + MatrizB->Itens[i][j];

	return MatrizR;
}

TMatriz* TMatriz_Multiplicar(TMatriz* MatrizA, TMatriz* MatrizB)
{
	size_t i, j, k;
	TMatriz* MatrizR;

	if (MatrizA->Colunas != MatrizB->Linhas)
	{
		printf("Erro (0x68). O numero de colunas da primeira matriz deve ser igual o numero de linhas da segunda matriz.\n");
		return NULL;
	}
	MatrizR = TMatriz_Criar(MatrizA->Linhas, MatrizB->Colunas);
	if (MatrizR == NULL)
		return NULL;
	for (i = 0; i < MatrizR->Colunas; i++)
		for (j = 0; j < MatrizR->Linhas; j++)
		{
			MatrizR->Itens[i][j] = 0;			
			for (k = 0; k < MatrizA->Linhas; k++)
				MatrizR->Itens[i][j] += MatrizA->Itens[i][k] * MatrizB->Itens[k][j];
		}
	return MatrizR;	
}

TMatriz* TMatriz_Subtrair(TMatriz* MatrizA, TMatriz* MatrizB)
{
	size_t i, j;
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
	for (i = 0; i < MatrizA->Linhas; i++)
		for (j = 0; j < MatrizA->Colunas; j++)
			MatrizR->Itens[i][j] = MatrizA->Itens[i][j] - MatrizB->Itens[i][j];

	return MatrizR;
}

void TMatriz_Imprimir(TMatriz* Matriz)
{
	size_t i, j;
	
	for (i = 0; i < Matriz->Linhas; i++)
	{
		for (j = 0; j < Matriz->Colunas; j++)
			printf("%d ", (int)Matriz->Itens[i][j]);
		printf("\n");
	}
	printf("\n");
}
