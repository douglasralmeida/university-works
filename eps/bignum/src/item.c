/*
**	ITEM DE UM TAD LISTA
**	DOUGLAS RODRIGUES DE ALMEIDA
**
**	Implementacao do item do TAD Lista para lista de inteiros
**	
**/

#include "item.h"

bool TListaItem_Salvar(TListaItem* Item, FILE* Arquivo)
{
	return (fprintf("%d", Item->Valor) >= 0);
}
