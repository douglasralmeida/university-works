/*
 *	TIPO ABSTRATO DE DADOS PILHA
 *	DOUGLAS RODRIGUES DE ALMEIDA
 *
 *	Cabeçalhos e estruturas de uma pilha encadeada por ponteiros
 */

#ifndef PILHA_H
#define PILHA_H

#include "core.h"

/* Estrutura do nó da pilha */
typedef struct _TPilhaNo* TPilhaNo;

struct _TPilhaNo {
	void* Item;			/* Guarda o item da pilha */
	TPilhaNo Proximo;	/* Aponta para o próximo nó da pilha */
};

/* Estrutura da pilha */
typedef struct _TPilha {
	TPilhaNo Frente;	/* Primeiro nó da pilha */
	size_t Tamanho;		/* Tamanho da pilha */
} TPilha;

/* ----------------------------------------------------------------------------
 * funcao:		TPilha_Criar
 * 				Cria uma pilha vazia
 * @param:		(vazio)
 * @retorna:	A pilha alocada
 *---------------------------------------------------------------------------*/ 
TPilha* TPilha_Criar();

/* ----------------------------------------------------------------------------
 * funcao:		TPilha_Destruir
 * 				Destroi a pilha
 * @param:		Pilha
 * @param:		Funcao que destroi um item da pilha
 * @retorna:	(vazio)
 *---------------------------------------------------------------------------*/ 
void TPilha_Destruir(TPilha** PPilha, TFuncaoDestruir FuncaoDestruir);

/* ----------------------------------------------------------------------------
 * funcao:		TPilha_Desempilhar
 * 				Remove e retorna o proximo item da pilha
 * @param:		Pilha
 * @retorna:	Item removido
 *---------------------------------------------------------------------------*/ 
void* TPilha_Desempilhar(TPilha* Pilha);

/* ----------------------------------------------------------------------------
 * funcao:		TPilha_Empilhar
 * 				Insere um item no final da pilha
 * @param:		Pilha
 * @param:		Item a ser inserido
 * @retorna:	(vazio)
 *---------------------------------------------------------------------------*/ 
bool TPilha_Empilhar(TPilha* Pilha, void* Item);

/* ----------------------------------------------------------------------------
 * funcao:		TPilha_Imprimir
 * 				Imprime a pilha na tela na ordem de saída
 * @param:		Pilha
 * @param:		Funcao que imprime um item da pilha
 * @retorna:	(vazio)
 *---------------------------------------------------------------------------*/ 
void TPilha_Imprimir(TPilha* Pilha, TFuncaoImprimir FuncaoImprimir);

/* ----------------------------------------------------------------------------
 * funcao:		TPilha_Limpar
 * 				Remove todos os itens da pilha
 * @param:		Pilha
 * @param:		Funcao que destroi um item da pilha
 * @retorna:	(vazio)
 *---------------------------------------------------------------------------*/ 
void TPilha_Limpar(TPilha* Pilha, TFuncaoDestruir FuncaoDestruir);

/* ----------------------------------------------------------------------------
 * funcao:		TPilha_Tamanho
 * 				Retorna o quantidade de itens da pilha
 * @param:		Pilha
 * @retorna:	Inteiro com o tamanho
 *---------------------------------------------------------------------------*/ 
size_t TPilha_Tamanho(TPilha* Pilha);

#endif
