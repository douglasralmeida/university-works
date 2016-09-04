/*
 *	TIPO ABSTRATO DE DADOS ARVORE DIGITAL
 *	DOUGLAS RODRIGUES DE ALMEIDA
 *
 *	Cabeçalhos e estruturas de uma arvore digital
 */

#ifndef TRIE_H
#define TRIE_H

#include "boolutils.h"

#define TAMANHO_ALFABETO 26

typedef struct _TArvoreDigitalNo* TArvoreDigitalNo;

typedef struct _TArvoreDigitalNo {
	TArvoreDigitalNo Alfabeto[TAMANHO_ALFABETO];
	unsigned long Contador;
	bool Sufixo;	
};

typedef struct _TArvoreDigital {
	TArvoreDigitalNo Raiz;			/* Guarda a raiz da árvore */
} TArvoreDigital;

TArvoreDigitalNo TArvoreDigitalNo_Criar();

void TArvoreDigitalNo_Destruir(TArvoreDigitalNo* PArvoreDigitalNo);

/* ----------------------------------------------------------------------------
 * funcao:		TArvoreDigital_Criar
 * 				Cria uma arvore digital vazia
 * @param:		(vazio)
 * @retorna:	A arvore digital alocada
 *---------------------------------------------------------------------------*/ 
TArvoreDigital* TArvoreDigital_Criar();

/* ----------------------------------------------------------------------------
 * funcao:		TArvoreDigital_Destruir
 * 				Destroi a arvore
 * @param:		Arvore
 * @retorna:	(vazio)
 *---------------------------------------------------------------------------*/ 
void TArvoreDigital_Destruir(TArvoreDigital** PArvore);

#endif
