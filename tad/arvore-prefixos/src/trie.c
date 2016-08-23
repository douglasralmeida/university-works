/*
 *	TIPO ABSTRATO DE DADOS ARVORE DIGITAL
 *	DOUGLAS RODRIGUES DE ALMEIDA
 *
 *	Implementação de uma arvore digital
 */

#include <stdio.h>
#include <stdlib.h>
#include "trie.h"

TArvoreDigital TArvoreDigital_Criar()
{
	TArvoreDigital NovaArvore;
	
	NovaArvore = malloc(sizeof(TArvoreDigital));
	NovaArvore->Raiz = NULL;
	
	return NovaArvore;
}

void TArvoreDigital_Destruir(TArvoreDigital** PArvore)
{
	
}