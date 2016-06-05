/*
**	TIPO ABASTRATO DE DADOS LISTA
**	DOUGLAS RODRIGUES DE ALMEIDA
**
**	Cabecalho e estruturas de lista duplamente encadeada por ponteiros
**	
**/

#ifndef LIST_H
#define LIST_H

#include <stdio.h>
#include <stdlib.h>
#include "boolutils.h"
#include "core.h"

/* Estrutura do no da lista */
typedef struct _TListaNo TListaNo;

struct _TListaNo {
	void* Item;
	TListaNo* Anterior;
	TListaNo* Proximo;
};

/* Estrutura da lista */
typedef struct _TLista {
	TFuncaoDestruir FuncaoDestruir;
	TFuncaoIguais FuncaoIguais;
	TFuncaoImprimir FuncaoImprimir;
	size_t Tamanho;
	TListaNo* Primeiro;
	TListaNo* Ultimo;
} TLista;

/* ----------------------------------------------------------------------------
 * funcao:		TLista_Criar
 * 				Cria uma lista vazia
 * @param:		Ponteiro para uma funcao que desaloca um item da memoria
 * @param:		Ponteiro para uma funcao de comparacao do conteudo de itens
 * @param:		Ponteiro para uma funcao que imprime um item
 * @retorna:	A lista alocada
 *---------------------------------------------------------------------------*/
TLista* TLista_Criar(TFuncaoDestruir FuncaoDestruir, TFuncaoIguais FuncaoIguais, TFuncaoImprimir FuncaoImprimir);

/* ----------------------------------------------------------------------------
 * funcao:		TLista_Destruir
 * 				Destroi a lista
 * @param:		Ponteiro para lista
 * @retorna:	(vazio)
 *---------------------------------------------------------------------------*/
void TLista_Destruir(TLista** PLista);

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
 * @retorna:	(vazio)
 *---------------------------------------------------------------------------*/
void TLista_Imprimir(TLista* Lista);

/* ----------------------------------------------------------------------------
 * funcao:		TLista_Inserir
 * 				Adiciona um item apos o no informado
 * @param:		Lista
 * @param:		Item a ser adicionado
 * @param:		No que antecedera o item a ser adicionado
 * @retorna:	True em caso de adicao com sucesso, ou false em caso de falha
 *---------------------------------------------------------------------------*/
bool TLista_Inserir(TLista* Lista, void* Item, TListaNo* No);

/* ----------------------------------------------------------------------------
 * funcao:		TLista_Item
 * 				Retorna o item da posicao informada
 * @param:		Lista
 * @param:		Posicao do item
 * @retorna:	O item solicitado
 *---------------------------------------------------------------------------*/
void* TLista_Item(TLista* Lista, const size_t Posicao);

/* ----------------------------------------------------------------------------
 * funcao:		TLista_Limpar
 * 				Remove todos os itens da lista
 * @param:		Lista
 * @retorna:	(vazio)
 *---------------------------------------------------------------------------*/
void TLista_Limpar(TLista* Lista);

/* ----------------------------------------------------------------------------
 * funcao:		TLista_Posicao
 * 				Retorna a posicao de um item da lista
 * @param:		Lista
 * @param:		Item a ser pesquisado
 * @retorna:	Posicao do item. Retorna zero em caso de inexistencia
 *---------------------------------------------------------------------------*/
size_t TLista_Posicao(TLista* Lista, void* Item);

/* ----------------------------------------------------------------------------
 * funcao:		TLista_Remover
 * 				Remove o no da lista
 * @param:		Lista
 * @param:		No a ser removido
 * @retorna:	(vazio)
 *---------------------------------------------------------------------------*/
void TLista_Remover(TLista* Lista, TListaNo* No);

/* ----------------------------------------------------------------------------
 * funcao:		TLista_Tamanho
 * 				Retorna a quantidade de itens da lista
 * @param:		Lista
 * @retorna:	O tamanho
 *---------------------------------------------------------------------------*/
size_t TLista_Tamanho(TLista* Lista);

/* ----------------------------------------------------------------------------
 * funcao:		TLista_Trocar
 * 				Troca dois nos de posicao
 * @param:		No a ser trocado
 * @param:		Outro no a ser trocado 
 * @retorna:	(vazio)
 *---------------------------------------------------------------------------*/
void TLista_Trocar(TLista* Lista, TListaNo* NoA, TListaNo* NoB);
#endif