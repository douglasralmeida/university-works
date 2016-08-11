/*
 *	TIPO ABSTRATO DE DADOS MATRIZ
 *	DOUGLAS RODRIGUES DE ALMEIDA
 *
 *	Implementação de uma matriz esparsa usando ponteiros
 */

#include <stdio.h>
#include <stdlib.h>
#include "matriz.h"

TMatriz* TMatriz_Criar(size_t NumLinhas, size_t NumColunas)
{
	TMatriz* NovaMatriz;

	NovaMatriz = malloc(sizeof(TMatriz));
	if (NovaMatriz == NULL)
	{
		printf("Erro (0x61): Erro ao alocar matriz.\n");
		return NULL;
	}
	NovaMatriz->Linhas = NumLinhas;
	NovaMatriz->Colunas = NumColunas;
	/*adicionar codigo aqui */
	return NovaMatriz;
}

void TMatriz_Destruir(TMatriz** PMatriz)
{
	size_t i;

	if (PMatriz != NULL)
	{
		/*adicionar codigo aqui */
		free(*PMatriz);
		*PMatriz = NULL;
	}
}

TMatriz* TMatriz_Adicionar(TMatriz* MatrizA, TMatriz* MatrizB)
{
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
	/*adicionar codigo aqui */
	return MatrizR;
}

TMatriz* TMatriz_Multiplicar(TMatriz* MatrizA, TMatriz* MatrizB)
{
	TMatriz* MatrizR;

	if (MatrizA->Colunas != MatrizB->Linhas)
	{
		printf("Erro (0x68). O numero de colunas da primeira matriz deve ser igual o numero de linhas da segunda matriz.\n");
		return NULL;
	}
	MatrizR = TMatriz_Criar(MatrizA->Linhas, MatrizB->Colunas);
	if (MatrizR == NULL)
		return NULL;
	/*adicionar codigo aqui */	
	
	return MatrizR;
}

TMatriz* TMatriz_Subtrair(TMatriz* MatrizA, TMatriz* MatrizB)
{
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
	/*adicionar codigo aqui */
	
	return MatrizR;
}

void TMatriz_Imprimir(TMatriz* Matriz)
{
	/*adicionar codigo aqui */
	printf("\n");
}
