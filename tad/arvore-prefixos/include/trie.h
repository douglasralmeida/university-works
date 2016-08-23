/*
 *	TIPO ABSTRATO DE DADOS ARVORE DIGITAL
 *	DOUGLAS RODRIGUES DE ALMEIDA
 *
 *	Cabeçalhos e estruturas de uma arvore digital
 */

#ifndef TRIE_H
#define TRIE_H

typedef struct _TArvoreDigitalNo* TArvoreDigitalNo;

typedef struct _TArvoreDigitalNo {
	TArvoreDigitalNo[26] Alfabeto;
	bool FimDePalavra;
};

typedef struct _TArvoreDigital {
	TArvoreDigitalNo Raiz;			/* Guarda a raiz da árvore */
} TArvoreDigital;

/* ----------------------------------------------------------------------------
 * funcao:		TArvoreDigital_Criar
 * 				Cria uma arvore digital vazia
 * @param:		(vazio)
 * @retorna:	A arvore digital alocada
 *---------------------------------------------------------------------------*/ 
TArvoreDigital TArvoreDigital_Criar();

/* ----------------------------------------------------------------------------
 * funcao:		TArvoreDigital_Destruir
 * 				Destroi a arvore
 * @param:		Arvore
 * @retorna:	(vazio)
 *---------------------------------------------------------------------------*/ 
void TArvoreDigital_Destruir(TArvoreDigital* PArvoreDigital);

#endif
