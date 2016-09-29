/*
 *	TIPO ABSTRATO DE DADOS ARVORE B MAIS
 *	DOUGLAS RODRIGUES DE ALMEIDA
 *
 *	Cabeçalhos e estruturas de uma arvore b+
 */

#ifndef ARVORE_BMAIS_H
#define ARVORE_BMAIS_H

#include "core.h"

/* Tipos de nó da arvore */
typedef enum {bmnoInterno, bmnoExterno} TArvoreBMNoTipo;

/* Estrutura do nó da arvore */
typedef struct _TArvoreBMNo* TArvoreBMNo;

struct _TArvoreBMNo {
	TArvoreBMNoTipo Tipo;
	union {
		struct _I {
			unsigned short Contador;
			void** Chaves;
			TArvoreBMNo* Subarvores;
		} Interno;
		struct _E {
			unsigned short Contador;
			void* Itens;	/* Guarda o itens da arvore */
		} Externo;
	} Conteudo;
};

typedef struct _TArvoreBMais {
	unsigned short Ordem;
	TArvoreBMNo Raiz;
} TArvoreBMais;

TArvoreBMNo TArvoreBMNo_Criar(TArvoreBMNoTipo Tipo, unsigned short Ordem, void* Item, TArvoreBMNo No1, TArvoreBMNo No2);

bool TArvoreBMNo_Inserir(TArvoreBMNo NoAtual, unsigned short Ordem, void* Item, TArvoreBMNo NoRetorno, void* ItemRetorno);


/* ----------------------------------------------------------------------------
 * funcao:		TArvoreBMais_Criar
 * 			Cria uma arvore vazia
 * @param:		Ordem da arvora a ser criada
 * @retorna:		A arvore alocada
 *---------------------------------------------------------------------------*/ 
TArvoreBMais* TArvoreBMais_Criar();

/* ----------------------------------------------------------------------------
 * funcao:		TArvoreBMais_Destruir
 * 			Destroi a arvore
 * @param:		Arvore
 * @param:		Funcao que destroi cada item da folha da árvore
 * @retorna:		(vazio)
 *---------------------------------------------------------------------------*/ 
void TArvoreBMais_Destruir(TArvoreBMais** PArvore, TFuncaoDestruir FuncaoDestruir);

bool TArvoreBMais_Inserir(TArvoreBMais* Arvore, void* Item);

void* TArvoreBMais_Pesquisar(TArvoreBMais* Arvore, void* Chave);

#endif
