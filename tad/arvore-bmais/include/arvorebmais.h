/*
 *	TIPO ABSTRATO DE DADOS ARVORE B MAIS
 *	DOUGLAS RODRIGUES DE ALMEIDA
 *
 *	Cabeçalhos e estruturas de uma arvore b+
 */

#ifndef ARVOREMAIS_H
#define ARVOREMAIS_H

#include "core.h"

/* Tipos de nó da arvore */
typedef enum {tnInterno, tnExterno} TArvoreBMNoTipo;

/* Estrutura do nó da arvore */
typedef struct _TArvoreBMNo* TArvoreBMNo;

struct _TArvoreBMNo {
	TArvoreBMNoTipo Tipo;
	union {
		struct _I {
			unsigned short Contador;
			void** Chaves;
			TArvoreBMNo* Filhos
		} Interno;
		struct _E {
			unsigned short Contador;
			void* Items;	/* Guarda o itens da arvore */
		} Externo;
	} Conteudo;
};

typedef struct _TArvoreBMais {
	unsigned short Ordem;
	TArvoreBMNo Raiz;
} TArvoreBM;

/* ----------------------------------------------------------------------------
 * funcao:		TArvoreBMais_Criar
 * 			Cria uma arvore vazia
 * @param:		Ordem da arvora a ser criada
 * @retorna:		A arvore alocada
 *---------------------------------------------------------------------------*/ 
TArvoreBMais* TArvoreBMais_Criar(unsigned short Ordem);

/* ----------------------------------------------------------------------------
 * funcao:		TArvoreBMais_Destruir
 * 			Destroi a arvore
 * @param:		Arvore
 * @param:		Funcao que destroi cada item da folha da árvore
 * @retorna:		(vazio)
 *---------------------------------------------------------------------------*/ 
void TArvoreBMais_Destruir(TArvoreBMais** PArvoreBMais, TFuncaoDestruir FuncaoDestruir);

#endif
