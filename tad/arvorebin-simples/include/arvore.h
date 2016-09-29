/*
 *	TIPO ABSTRATO DE DADOS ARVORE BINARIA
 *	DOUGLAS RODRIGUES DE ALMEIDA
 *
 *	Cabeçalhos e estruturas de uma arvore binaria sem balaceamento
 */

#ifndef ARVORE_H
#define ARVORE_H

/* Estrutura do nó da arvore */
typedef struct _TArvoreNo* TArvoreNo;

struct _TArvoreNo {
	void* Item;		/* Guarda o item da fila */
	TArvoreNo Esquerda;	/* Aponta para o filho esquerdo do nó */
	TArvoreNo Direita;	/* Aponta para o filho direito do nó */
};

typedef TArvoreNo TArvore;

/* ----------------------------------------------------------------------------
 * funcao:		TArvore_Criar
 * 				Cria uma arvore vazia
 * @param:		(vazio)
 * @retorna:	A arvore alocada
 *---------------------------------------------------------------------------*/ 
TArvore TArvore_Criar();

/* ----------------------------------------------------------------------------
 * funcao:		TArvore_Destruir
 * 				Destroi a arvore
 * @param:		Arvore
 * @param:		Funcao que destroi um item do nó da árvore
 * @retorna:	(vazio)
 *---------------------------------------------------------------------------*/ 
void TArvore_Destruir(TArvore* PArvore, TFuncaoDestruir FuncaoDestruir);

#endif
