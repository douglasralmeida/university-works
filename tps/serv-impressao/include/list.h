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
	size_t Tamanho;
	TListaNo* Primeiro;
	TListaNo* Ultimo;
} TLista;

/* Cria uma lista vazia */
TLista* TLista_Criar(TFuncaoDestruir FuncaoDestruir);

/* Destroi a lista */
void TLista_Destruir(TLista** PLista);

/* Adidiona um item ao fim da lista */
bool TLista_Adicionar(TLista* Lista, void* Item);

/* Checa se a lista esta vazia */
bool TLista_EstaVazia(TLista* Lista);

/* Imprime uma lista na tela */
void TLista_Imprimir(TLista* Lista);

/* Adiciona um item apos o no informado */
bool TLista_Inserir(TLista* Lista, void* Item, TListaNo* No);

/* Retorna o item da posicao informada */
TListaItem TLista_Item(TLista* Lista, const unsigned int Posicao);

/* Remove todos os itens da lista */
void TLista_Limpar(TLista* Lista);

/* Remove o no da lista */
void TLista_Remover(TLista* Lista, TListaNo* No);

/* Retorna o tamanho da lista */
unsigned int TLista_Tamanho(TLista* Lista);

/* Grava a lista em um arquivo */
bool TLista_SalvarNoArquivo(TLista* Lista, FILE* Arquivo);

/* Troca dois nos de posicao */
void TLista_Trocar(TLista* Lista, TListaNo* NoA, TListaNo* NoB);
#endif
