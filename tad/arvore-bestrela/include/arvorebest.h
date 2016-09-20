/*
 *	TIPO ABSTRATO DE DADOS ARVORE B ESTRELA
 *	DOUGLAS RODRIGUES DE ALMEIDA
 *
 *	Cabeçalhos e estruturas de uma arvore b*
 */

#ifndef ARVOREBEST_H
#define ARVOREBEST_H

#include "core.h"

/* Tipos de nó da arvore */
typedef enum {tnInterno, tnExterno} TArvoreBENoTipo;

/* Estrutura do nó da arvore */
typedef struct _TArvoreBENo* TArvoreBENo;

struct _TArvoreBENo {
	TArvoreBENoTipo Tipo;
	union {
		struct _I {
			unsigned short Contador;
			void** Chaves;
			TArvoreBENo* Filhos
		} Interno;
		struct _E {
			unsigned short Contador;
			void* Items;	/* Guarda o itens da arvore */
		} Externo;
	} Conteudo;
};

typedef struct _TArvoreBE {
	unsigned short Ordem;
	TArvoreBENo Raiz;
} TArvoreBE;

/* ----------------------------------------------------------------------------
 * funcao:		TArvoreBE_Criar
 * 			Cria uma arvore vazia
 * @param:		Ordem da arvora a ser criada
 * @retorna:		A arvore alocada
 *---------------------------------------------------------------------------*/ 
TArvoreBE* TArvoreBE_Criar(unsigned short Ordem);

/* ----------------------------------------------------------------------------
 * funcao:		TArvoreBE_Destruir
 * 			Destroi a arvore
 * @param:		Arvore
 * @param:		Funcao que destroi cada item da folha da árvore
 * @retorna:		(vazio)
 *---------------------------------------------------------------------------*/ 
void TArvoreBE_Destruir(TArvoreBE** PArvoreBE, TFuncaoDestruir FuncaoDestruir);

#endif
