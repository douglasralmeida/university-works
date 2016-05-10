/*
**	ITEM DE UM TAD LISTA
**	DOUGLAS RODRIGUES DE ALMEIDA
**
**	Implementacao do item do TAD Lista para lista de inteiros
**	
**/

#include "item.h"

bool TListaItem_SalvarNoArquivo(TListaItem* Item, FILE* Arquivo)
{
	return (fprintf(Arquivo, "%ud", Item->Valor) >= 0);
}
