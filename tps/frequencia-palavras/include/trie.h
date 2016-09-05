/*
 *	TIPO ABSTRATO DE DADOS ARVORE DIGITAL
 *	DOUGLAS RODRIGUES DE ALMEIDA
 *
 *	Cabeçalhos e estruturas de uma arvore digital
 */

#ifndef TRIE_H
#define TRIE_H

#include <stdio.h>
#include "boolutils.h"

#define TAMANHO_ALFABETO 26

typedef struct _TArvoreDigitalNo* TArvoreDigitalNo;

struct _TArvoreDigitalNo {
	TArvoreDigitalNo* Alfabeto;
	unsigned long Contador;
	bool Sufixo;	
};

typedef struct _TArvoreDigital {
	TArvoreDigitalNo Raiz;			/* Guarda a raiz da árvore */
} TArvoreDigital;

/* ----------------------------------------------------------------------------
 * funcao:	TArvoreDigitalNo_Criar
 * 		Cria um nó de arvore digital vazio
 * @param:	(vazio)
 * @retorna:	No
 *---------------------------------------------------------------------------*/ 
TArvoreDigitalNo TArvoreDigitalNo_Criar();

/* ----------------------------------------------------------------------------
 * funcao:	TArvoreDigitalNo_Destruir
 * 		Destroi um nó de arvore digital
 * @param:	No da arvore
 * @retorna:	(vazio)
 *---------------------------------------------------------------------------*/
void TArvoreDigitalNo_Destruir(TArvoreDigitalNo* PArvoreDigitalNo);

/* ----------------------------------------------------------------------------
 * funcao:	TArvoreDigitalNo_ExibirContador
 * 		Exibe o valor do contador armazenado no nó
 * @param:	No
 * @retorna:	(vazio)
 *---------------------------------------------------------------------------*/
void TArvoreDigitalNo_ExibirContador(TArvoreDigitalNo No);

/* ----------------------------------------------------------------------------
 * funcao:	TArvoreDigital_Criar
 * 		Cria uma arvore digital vazia
 * @param:	(vazio)
 * @retorna:	Arvore
 *---------------------------------------------------------------------------*/ 
TArvoreDigital* TArvoreDigital_Criar();

/* ----------------------------------------------------------------------------
 * funcao:	TArvoreDigital_Destruir
 * 		Destroi a arvore
 * @param:	Arvore
 * @retorna:	(vazio)
 *---------------------------------------------------------------------------*/ 
void TArvoreDigital_Destruir(TArvoreDigital** PArvore);

void TArvoreDigital_Adicionar(TArvoreDigital* Arvore, char* Palavra);

void TArvoreDigital_Carregar(TArvoreDigital* Arvore, FILE* Arquivo);

void TArvoreDigital_ContarPalavras(TArvoreDigital* Arvore, FILE* Arquivo);

void TArvoreDigital_ExibirContador(TArvoreDigital* Arvore);
#endif
