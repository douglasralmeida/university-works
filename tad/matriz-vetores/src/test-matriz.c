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
	
	TMatriz_AlterarItem(Matriz, 1, 1, 3);
	TMatriz_AlterarItem(Matriz, 1, 2, 4);
	TMatriz_AlterarItem(Matriz, 2, 1, 5);
	TMatriz_AlterarItem(Matriz, 2, 2, 6);

	Matriz2 = TMatriz_Criar(2, 2);
	
	TMatriz_AlterarItem(Matriz2, 1, 1, 2);
	TMatriz_AlterarItem(Matriz2, 1, 2, 2);
	TMatriz_AlterarItem(Matriz2, 2, 1, 2);
	TMatriz_AlterarItem(Matriz2, 2, 2, 2);

	Matriz3 = TMatriz_Multiplicar(Matriz, Matriz2);
	
	TMatriz_Imprimir(Matriz3);	
	
	TMatriz_Destruir(&Matriz);
	TMatriz_Destruir(&Matriz2);
	TMatriz_Destruir(&Matriz3);
	
	exit(EXIT_SUCCESS);
}

