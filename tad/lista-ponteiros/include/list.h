/*
**	TIPO ABASTRATO DE DADOS LISTA
**	DOUGLAS RODRIGUES DE ALMEIDA
**
**	Cabeçalhos e estruturas de lista duplamente encadeada por ponteiros
**	
**/

#ifndef LIST_H
#define LIST_H

#include "boolutils.h"
#include "core.h"

/* Estrutura do no da lista */
typedef struct _TListaNo* TListaNo;

struct _TListaNo {
	void* Item;		/* Guarda o item da lista */
	TListaNo Anterior;	/* Aponta para o nó anterior da lista */
	TListaNo Proximo;	/* Aponta para o próximo nó da lista */
};

/* Estrutura da lista */
typedef struct _TLista {
	size_t Tamanho;		/* Tamanho da lista */
	TListaNo Primeiro;	/* Primeiro nó da lista */
	TListaNo Ultimo;	/* Último nó da lista */
} TLista;

/* ----------------------------------------------------------------------------
 * funcao:		TLista_Criar
 *			Cria uma lista vazia
 * @param:		(vazio)
 * @retorna:		A lista alocada
 *---------------------------------------------------------------------------*/
TLista* TLista_Criar(void);

/* ----------------------------------------------------------------------------
 * funcao:		TLista_Destruir
 * 			Destrói a lista
 * @param:		Lista
 * @param:		Funcao que destrói um item da lista
 * @retorna:		(vazio)
 *---------------------------------------------------------------------------*/
void TLista_Destruir(TLista** PLista, TFuncaoDestruir FuncaoDestruir);

/* ----------------------------------------------------------------------------
 * funcao:		TLista_Adicionar
 * 			Adiciona um item ao fim da lista
 * @param:		Lista
 * @param:		Item a ser adicionado
 * @retorna:		True em caso de adicao com sucesso, ou false em caso de falha
 *---------------------------------------------------------------------------*/
bool TLista_Adicionar(TLista* Lista, void* Item);

/* ----------------------------------------------------------------------------
 * funcao:		TLista_Imprimir
 * 			Imprime uma lista na tela
 * @param:		Lista
 * @param:		Funcao que imprime um item da lista
 * @retorna:		(vazio)
 *---------------------------------------------------------------------------*/
void TLista_Imprimir(TLista* Lista, TFuncaoImprimir FuncaoImprimir);

/* ----------------------------------------------------------------------------
 * funcao:		TLista_Inserir
 * 			Adiciona um item apos o no informado
 * @param:		Lista
 * @param:		Item a ser adicionado
 * @param:		No que antecedera o item a ser adicionado
 * @retorna:		True em caso de adicao com sucesso, ou false em caso de falha
 *---------------------------------------------------------------------------*/
bool TLista_Inserir(TLista* Lista, void* Item, TListaNo No);

/* ----------------------------------------------------------------------------
 * funcao:		TLista_Item
 * 			Retorna o item da posicao informada
 * @param:		Lista
 * @param:		Posicao do item
 * @retorna:		O item solicitado
 *---------------------------------------------------------------------------*/
void* TLista_Item(TLista* Lista, const size_t Posicao);

/* ----------------------------------------------------------------------------
 * funcao:		TLista_Limpar
 * 			Remove todos os itens da lista
 * @param:		Lista
 * @param:		Funcao que destrói um item da lista
 * @retorna:		(vazio)
 *---------------------------------------------------------------------------*/
void TLista_Limpar(TLista* Lista, TFuncaoDestruir FuncaoDestruir);

/* ----------------------------------------------------------------------------
 * funcao:		TLista_Pesquisar
 * 			Pesquisa sequencial de um item na lista
 * @param:		Lista
 * @param:		Item a ser pesquisado
 * @param:		Funcao de comparacao do conteudo de dois itens
 * @retorna:		No da lista que armazena o item ou nulo em caso de pesquisa vazia
 *---------------------------------------------------------------------------*/
TListaNo TLista_Pesquisar(TLista* Lista, void* Item, TFuncaoIguais FuncaoIguais);

/* ----------------------------------------------------------------------------
 * funcao:		TLista_Posicao
 * 			Retorna a posicao de um item da lista
 * @param:		Lista
 * @param:		Item a ser pesquisado
 * @param:		Funcao de comparacao do conteudo de dois itens
 * @retorna:		Posicao do item. Retorna zero em caso de inexistencia
 *---------------------------------------------------------------------------*/
size_t TLista_Posicao(TLista* Lista, void* Item, TFuncaoIguais FuncaoIguais);

/* ----------------------------------------------------------------------------
 * funcao:		TLista_Remover
 * 			Remove o no da lista
 * @param:		Lista
 * @param:		No a ser removido
 * @param:		Funcao que destrói um item da memoria
 * @retorna:		(vazio)
 *---------------------------------------------------------------------------*/
void TLista_Remover(TLista* Lista, TListaNo No, TFuncaoDestruir FuncaoDestruir);

/* ----------------------------------------------------------------------------
 * funcao:		TLista_Tamanho
 * 			Retorna a quantidade de itens da lista
 * @param:		Lista
 * @retorna:		Seu tamanho
 *---------------------------------------------------------------------------*/
size_t TLista_Tamanho(TLista* Lista);

/* ----------------------------------------------------------------------------
 * funcao:		TLista_Trocar
 * 			Troca dois nos de posicao
 * @param:		No a ser trocado
 * @param:		Outro no a ser trocado 
 * @retorna:		(vazio)
 *---------------------------------------------------------------------------*/
void TLista_Trocar(TListaNo NoA, TListaNo NoB);
#endif
