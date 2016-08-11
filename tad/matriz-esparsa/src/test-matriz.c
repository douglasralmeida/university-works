/*
**	TESTE DO TAD MATRIZ
**	DOUGLAS RODRIGUES DE ALMEIDA
**
**	Teste do TAD Matriz
**	
**/

#include <stdio.h>
#include <stdlib.h>
#include "matriz.h"

int main(void)
{	
	TMatriz* Matriz;
	TMatriz* Matriz2;
	TMatriz* Matriz3;
	
	Matriz = TMatriz_Criar(2, 2);
	
	Matriz->Itens[0][0] = 3;
	Matriz->Itens[0][1] = 4;
	Matriz->Itens[1][0] = 5;
	Matriz->Itens[1][1] = 6;

	Matriz2 = TMatriz_Criar(2, 2);
	
	Matriz2->Itens[0][0] = 2;
	Matriz2->Itens[0][1] = 2;
	Matriz2->Itens[1][0] = 2;
	Matriz2->Itens[1][1] = 2;

	Matriz3 = TMatriz_Multiplicar(Matriz, Matriz2);
	
	TMatriz_Imprimir(Matriz3);	
	
	TMatriz_Destruir(&Matriz);
	TMatriz_Destruir(&Matriz2);
	TMatriz_Destruir(&Matriz3);
	
	exit(EXIT_SUCCESS);
}

