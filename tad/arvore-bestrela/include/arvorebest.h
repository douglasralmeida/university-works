/*
 *	TIPO ABSTRATO DE DADOS ARVORE B ESTRELA
 *	DOUGLAS RODRIGUES DE ALMEIDA
 *
 *	Cabeçalhos e estruturas de uma arvore b*
 */

#ifndef ARVOREBEST_H
#define ARVOREBEST_H

#include "core.h"

/* Estrutura do nó da arvore */
typedef struct _TArvoreBENo* TArvoreBENo;

struct _TArvoreBENo {
	unsigned short Contador;
	void** Itens;
	TArvoreBENo* Subarvores;
};

typedef struct _TArvoreBEstrela {
	unsigned short Ordem;
	TArvoreBENo Raiz;
} TArvoreBEstrela;

/* ----------------------------------------------------------------------------
 * funcao:		TArvoreBEstrela_Criar
 * 			Cria uma arvore vazia
 * @param:		Ordem da arvora a ser criada
 * @retorna:		A arvore alocada
 *---------------------------------------------------------------------------*/ 
TArvoreBEstrela* TArvoreBEstrela_Criar(unsigned short Ordem);

/* ----------------------------------------------------------------------------
 * funcao:		TArvoreBEstrela_Destruir
 * 			Destroi a arvore
 * @param:		Arvore
 * @param:		Funcao que destroi cada item da folha da árvore
 * @retorna:		(vazio)
 *---------------------------------------------------------------------------*/ 
void TArvoreBEstrela_Destruir(TArvoreBEstrela** PArvore, TFuncaoDestruir FuncaoDestruir);

void TArvoreBEstrela_Inserir(TArvoreBEstrela* Arvore, void* Item);

#endif
