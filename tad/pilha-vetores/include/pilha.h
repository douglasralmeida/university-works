/*
 *	TIPO ABSTRATO DE DADOS PILHA
 *	DOUGLAS RODRIGUES DE ALMEIDA
 *
 *	Cabeçalhos e estruturas de uma pilha por vetores
 */

#ifndef PILHA_H
#define PILHA_H

#include "boolutils.h"
#include "core.h"

#define PILHA_EXPANSAO 1024

/* Nó da pilha */
typedef size_t TPilhaNo;

/* Estrutura da pilha */
typedef struct _TPilha {
	size_t Capacidade;	/*-- Capacidade de armazenamento atual da pilha --*/
	size_t Expansao;	/*-- Capacidade de autoexpansão da pilha --*/
	TPilhaNo Frente;	/*-- Primeiro item da pilha --*/
	void** Itens;		/*-- Conteúdo da pilha --*/
} TPilha;

/* ----------------------------------------------------------------------------
 * funcao:		TPilha_Criar
 * 			Cria uma pilha vazia
 * @param:		Capacidade inicial da pilha
 * @retorna:		A pilha alocada
 *---------------------------------------------------------------------------*/ 
TPilha* TPilha_Criar(size_t Capacidade);

/* ----------------------------------------------------------------------------
 * funcao:		TPilha_Destruir
 * 			Destroi a pilha
 * @param:		Pilha
 * @param:		Funcao que destroi um item da pilha
 * @retorna:		(vazio)
 *---------------------------------------------------------------------------*/ 
void TPilha_Destruir(TPilha** PPilha, TFuncaoDestruir FuncaoDestruir);

/* ----------------------------------------------------------------------------
 * funcao:		TPilha_Desempilhar
 * 			Remove e retorna o proximo item da pilha
 * @param:		Pilha
 * @retorna:		Item removido
 *---------------------------------------------------------------------------*/ 
void* TPilha_Desempilhar(TPilha* Pilha);

/* ----------------------------------------------------------------------------
 * funcao:		TPilha_Empilhar
 * 			Insere um item no final da pilha
 * @param:		Pilha
 * @param:		Item a ser inserido
 * @retorna:		(vazio)
 *---------------------------------------------------------------------------*/ 
bool TPilha_Empilhar(TPilha* Pilha, void* Item);

/* ----------------------------------------------------------------------------
 * funcao:		TPilha_Imprimir
 * 			Imprime a pilha na tela em ordem de saída
 * @param:		Pilha
 * @param:		Funcao que imprime um item da pilha
 * @retorna:		(vazio)
 *---------------------------------------------------------------------------*/ 
void TPilha_Imprimir(TPilha* Pilha, TFuncaoImprimir FuncaoImprimir);

/* ----------------------------------------------------------------------------
 * funcao:		TPilha_Limpar
 * 			Remove todos os itens da pilha
 * @param:		Pilha
 * @param:		Funcao que destroi um item da pilha
 * @retorna:		(vazio)
 *---------------------------------------------------------------------------*/ 
void TPilha_Limpar(TPilha* Pilha, TFuncaoDestruir FuncaoDestruir);

/* ----------------------------------------------------------------------------
 * funcao:		TPilha_Tamanho
 * 			Retorna o quantidade de itens da pilha
 * @param:		Pilha
 * @retorna:		Inteiro com o tamanho
 *---------------------------------------------------------------------------*/ 
size_t TPilha_Tamanho(TPilha* Pilha);

#endif
