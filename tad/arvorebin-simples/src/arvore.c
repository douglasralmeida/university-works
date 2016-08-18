/*
 *	TIPO ABSTRATO DE DADOS ARVORE BINARIA
 *	DOUGLAS RODRIGUES DE ALMEIDA
 *
 *	Implementação de uma arvore binaria sem balaceamento
 */

#ifndef ARVORE_H
#define ARVORE_H

#include <stdio.h>
#include <stdlib.h>
#include "arvore.h"

TArvore TArvore_Criar()
{
	TArvore NovaArvore;
	
	NovaArvore = malloc(sizeof(TArvore));
	if (NovaArvore == NULL)
		return NULL;
	NovaArvore->Item = NULL;
	NovaArvore->Direita = NULL;
	NovaArvore->Esquerda = NULL;
	
	return NovaArvore;
}

void TArvore_Destruir(TArvore* PArvore, TFuncaoDestruir FuncaoDestruir)
{
	
}
#endif
