/*
**	ITEM DE UM TAD LISTA
**	DOUGLAS RODRIGUES DE ALMEIDA
**
**	Cabecalho do item do TAD Lista para lista de inteiros
**	
**/

#ifndef ITEM_H
#define ITEM_H

#include <stdio.h>
#include "boolutils.h"

/* Estrutura do Item de Lista para listas de inteiros */
typedef struct _TListaItem {
	unsigned short Valor;
} TListaItem;

/* Imprime um item na tela */
void TListaItem_Imprimir(TListaItem* Item);

/* Grava o item em um arquivo */
bool TListaItem_SalvarNoArquivo(TListaItem* Item, FILE* Arquivo);

#endif
