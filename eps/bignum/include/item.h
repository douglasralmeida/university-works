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

typedef struct _TListaItem {
	unsigned short Valor;
} TListaItem;

//Grava o item em um arquivo
bool TListaItem_SalvarNoArquivo(TListaItem* Item, FILE* Arquivo);

#endif
