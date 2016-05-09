/*
**	TIPO ABASTRATO DE DADOS LISTA
**	DOUGLAS RODRIGUES DE ALMEIDA
**
**	Cabecalho do TAD Lista
**	
**/

#ifndef LIST_H
#define LIST_H

#include <stdio.h>
#include <stdlib.h>
#include "boolutils.h"
#include "item.h"

typedef struct _TListaNo {
	TListaItem Item;
	TListaNo* Anterior;
	TListaNo* Proximo;
} TListaNo;

typedef struct _TLista {
	unsigned int Tamanho;
	TListaNo* Primeiro;
	TListaNo* Ultimo;
} TLista;

//Cria uma lista vazia
TLista* TList_Criar(void);

//Destroi a lista
void TLista_Destruir(TLista** PLista);

//Adidiona um item ao fim da lista
void TLista_Adicionar(TLista* Lista, const TListaItem Item);

//Checa se a lista esta vazia
bool TLista_EstaVazia(TLista* Lista);

//Adiciona um item apos o no informado
void TLista_Inserir(TLista* Lista, const TListaItem Item, TListaNo* No);

//Remove todos os itens da lista
void TLista_Limpar(TLista* Lista);

//Remove o no da lista
void TLista_Remover(TLista* Lista, TListaNo* No);

//Retorna o item dentro do no e aponta para o proximo no conforme direcao escolhida
void TLista_Item(TLista* Lista, TListaNo* No, TListaItem* Item, const short Direcao)

//Retorna o tamanho da lista
unsigned int TLista_Tamanho(TLista* Lista);

//Grava a lista em um arquivo
bool TLista_SalvarNoArquivo(TLista* Lista, FILE* Arquivo);

//Troca dois nos de posicao
void TLista_Trocar(TLista* Lista, TListaNo* NoA, TListaNo* NoB);
#endif
