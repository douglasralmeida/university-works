/*
 *	TIPO ABSTRATO DE DADOS ARVORE B ESTRELA
 *	DOUGLAS RODRIGUES DE ALMEIDA
 *
 *	Implementação de uma arvore b*
 */

#ifndef ARVORE_H
#define ARVORE_H

#include <stdio.h>
#include <stdlib.h>
#include "arvorebest.h"

TArvoreBENo TArvoreBENo_Criar(TArvoreBENoTipo Tipo, unsigned short Ordem)
{
	TArvoreBENo NovoNo;

	NovoNo = malloc(sizeof(struct _TArvoreBENo));
	if (!NovoNo)
		return NULL;
	NovoNo->Contador = 0;
	NovoNo->Itens = malloc(Ordem * sizeof(void*));
	NovoNo->Subarvores = malloc((Ordem+1) * sizeof(TArvoreBENo*));

	return NovoNo;
}

TArvoreBE* TArvoreBE_Criar(unsigned short Ordem)
{
	TArvoreBE* NovaArvore;
	
	NovaArvore = malloc(sizeof(TArvoreBE));
	if (!NovaArvore)
		return NULL;
	if (Ordem)
		NovaArvore->Ordem = Ordem;
	else
	{
		free(NovaArvore);
		return NULL;
	}
	NovaArvore->Raiz = NULL;
	
	return NovaArvore;
}

void TArvoreBE_Destruir(TArvoreBE** PArvoreBE, TFuncaoDestruir FuncaoDestruir)
{
	/*-- destruir todos os nós --*/	
	free(*PArvoreBE);
	PArvoreBE = NULL;
}
#endif
