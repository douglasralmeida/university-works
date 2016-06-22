/*
**	TIPO ABASTRATO DE DADOS LISTA
**	DOUGLAS RODRIGUES DE ALMEIDA
**
**	Cabecalho e estruturas de lista implementada como um vetor
**	
**/

#ifndef LIST_H
#define LIST_H

#include <stdio.h>
#include <stdlib.h>
#include "boolutils.h"
#include "core.h"

#define LISTA_EXPANSAO 1024

/* No da lista */
typedef int TListaNo;

/* Estrutura da lista */
typedef struct _TLista {
	int Capacidade;
	int Expansao;
	void** Itens;
	TListaNo Primeiro;
	int Tamanho;
	TListaNo Ultimo;
} TLista;

/* ----------------------------------------------------------------------------
 * funcao:		TLista_Criar
 * 				Cria uma lista vazia
 * @param:		Capacidade de armazenamento inicial da lista
 * @retorna:	A lista alocada
 *---------------------------------------------------------------------------*/
TLista* TLista_Criar(int Capacidade);

/* ----------------------------------------------------------------------------
 * funcao:		TLista_Destruir
 * 				Destroi a lista
 * @param:		Ponteiro para lista
 * @param:		Ponteiro para uma funcao que desaloca um item da memoria
 * @retorna:	(vazio)
 *---------------------------------------------------------------------------*/
void TLista_Destruir(TLista** PLista, TFuncaoDestruir FuncaoDestruir);

/* ----------------------------------------------------------------------------
 * funcao:		TLista_Adicionar
 * 				Adiciona um item ao fim da lista
 * @param:		Lista
 * @param:		Item a ser adicionado
 * @retorna:	True em caso de adicao com sucesso, ou false em caso de falha
 *---------------------------------------------------------------------------*/
bool TLista_Adicionar(TLista* Lista, void* Item);

/* ----------------------------------------------------------------------------
 * funcao:		TLista_Imprimir
 * 				Imprime uma lista na tela
 * @param:		Lista
 * @param:		Ponteiro para uma funcao que imprime um item
 * @retorna:	(vazio)
 *---------------------------------------------------------------------------*/
void TLista_Imprimir(TLista* Lista, TFuncaoImprimir FuncaoImprimir);

/* ----------------------------------------------------------------------------
 * funcao:		TLista_Item
 * 				Retorna o item da posicao informada
 * @param:		Lista
 * @param:		Posicao do item
 * @retorna:	O item solicitado
 *---------------------------------------------------------------------------*/
void* TLista_Item(TLista* Lista, const TListaNo Posicao);

/* ----------------------------------------------------------------------------
 * funcao:		TLista_Limpar
 * 				Remove todos os itens da lista
 * @param:		Lista
 * @param:		Ponteiro para uma funcao que desaloca um item da memoria
 * @retorna:	(vazio)
 *---------------------------------------------------------------------------*/
void TLista_Limpar(TLista* Lista, TFuncaoDestruir FuncaoDestruir);

/* ----------------------------------------------------------------------------
 * funcao:		TLista_Ordenar
 * 				Ordena os itens da lista usando o metodo de Quicksort
 * @param:		Lista
 * @param:		Funcao de comparacao
 * @retorna:	(vazio)
 *---------------------------------------------------------------------------*/
void TLista_Ordenar(TLista* Lista, TFuncaoComparar FuncaoComparar);

/* ----------------------------------------------------------------------------
 * funcao:		TLista_Pesquisar
 * 				Pesquisa um item na lista
 * @param:		Lista
 * @param:		Item a ser pesquisado
 * @param:		Ponteiro para uma funcao de comparacao do conteudo dos itens
 * @retorna:	No da lista que armazena o item
 *---------------------------------------------------------------------------*/
TListaNo TLista_Pesquisar(TLista* Lista, void* Item, TFuncaoIguais FuncaoIguais);

/* ----------------------------------------------------------------------------
 * funcao:		TLista_Posicao
 * 				Retorna a posicao de um item da lista
 * @param:		Lista
 * @param:		Item a ser pesquisado
 * @param:		Ponteiro para uma funcao de comparacao do conteudo dos itens
 * @retorna:	Posicao do item. Retorna zero em caso de inexistencia
 *---------------------------------------------------------------------------*/
int TLista_Posicao(TLista* Lista, void* Item, TFuncaoIguais FuncaoIguais);

/* ----------------------------------------------------------------------------
 * funcao:		TLista_Proximo
 * 				Retorna o proximo no da lista
 * @param:		Lista
 * @param:		No
 * @retorna:	O proximo no, caso ele exista. -1 caso contrario
 *---------------------------------------------------------------------------*/
TListaNo TLista_Proximo(TLista* Lista, TListaNo No);

/* ----------------------------------------------------------------------------
 * funcao:		TLista_Remover
 * 				Remove o no da lista
 * @param:		Lista
 * @param:		No a ser removido
 * @param:		Ponteiro para uma funcao que desaloca um item da memoria
 * @retorna:	(vazio)
 *---------------------------------------------------------------------------*/
void TLista_Remover(TLista* Lista, TListaNo No, TFuncaoDestruir FuncaoDestruir);

/* ----------------------------------------------------------------------------
 * funcao:		TLista_Tamanho
 * 				Retorna a quantidade de itens da lista
 * @param:		Lista
 * @retorna:	O tamanho
 *---------------------------------------------------------------------------*/
int TLista_Tamanho(TLista* Lista);

/* ----------------------------------------------------------------------------
 * funcao:		TLista_Trocar
 * 				Troca dois nos de posicao
 * @param:		No a ser trocado
 * @param:		Outro no a ser trocado 
 * @retorna:	(vazio)
 *---------------------------------------------------------------------------*/
void TLista_Trocar(TLista* Lista, TListaNo NoA, TListaNo NoB);
#endif
