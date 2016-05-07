/*
**	TIPO ABASTRATO DE DADOS LISTA
**	DOUGLAS RODRIGUES DE ALMEIDA
**
**	Cabecalho do TAD Lista
**	
**/

#ifndef LIST_H
#define LIST_H

typedef struct _TListaNo {
	TListaItem Item;
	TListaNo* Prox;
} TListaNo;

typedef struct _TLista {
	unsigned int Tamanho;
	TListaNo* Primeiro;
	TListaNo* Ultimo;
} TLista;

//Create an empty list
TLista* TList_Criar(void);

//Destroy the list
void TLista_Destruir(TLista** PLista);

//Add an item to the list at end
void TLista_Adicionar(TLista* Lista, TListaItem Item);

//Remove all list items
void TLista_Limpar(TLista* Lista);

//Swap position of two list itens
void TLista_Trocar(TListaNo* NoA, TListaNo* NoB);

//Add an item after the list node
void TLista_Inserir(TLista* Lista, TListaItem Item, TListaNo* No);

//Remove the item of the list
void TLista_Remover(TLista* Lista, TListaNo* No);

#endif
