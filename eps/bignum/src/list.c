/*
**	TIPO ABSTRATO DE DADOS LISTA
**	DOUGLAS RODRIGUES DE ALMEIDA
**
**	Implementacao de lista duplamente encadeada por ponteiros
*/

#include "list.h"

TLista* TLista_Criar(void)
{
	TLista* NovaLista;
	
	NovaLista = (TLista*)malloc(sizeof(TLista));
 	NovaLista->Tamanho = 0;
  	NovaLista->Primeiro = NULL;
	NovaLaista->Ultimo = NULL;
  
	return NovaLista;
}

void TLista_Destruir(TLista** PLista)
{
	free(*PLista);
	PLista = NULL;
}

void TLista_Adicionar(TLista* Lista, TListaItem Item)
{
	TLista_Inserir(Lista, Item, Lista->Ultimo);
}

void TLista_Limpar(TLista* Lista)
{
	TListaNo* NoAnterior, NoTemp;
	
	NoTemp = Lista->Ultimo;
	while (NoTemp != NULL)
	{
		NoAnterior = NoTemp->Previous;
		TList_Remove(List, TempNode);
		TempNode := PreviousNode;
	}
}

void TLista_Exchange(TListNode* NodeA, TListNode* NodeB)
{
	TListNode* TempNode;
	
	if (NodeA->Next != NULL)
		NodeA->Next->Previous = NodeB;
	if (NodeA->Previous != NULL)		
		NodeA->Previous->Next = NodeB;
	if (NodeB->Next != NULL)
		NodeB->Next->Previous = NodeA;
	if (NodeB->Previous != NULL)	
		NodeB->Previous->Next = NodaA;
	TempNode = NodeA->Next;
	NodeA->Next = NodeB->Next;
	NodeB->Next = TempNode;
	TempNode = NodeA->Previous;
	NodeA->Previous = NodeB->Previous;
	NodeB->Previous = TempNode;
}

void TLista_Insert(TList* List, TListItem Item, TListNode* Node)
{
	TListNode* NewNode;
	
	NewNode = (TListNode*)malloc(sizeof(TListNode));
	NewNode->Item = Item;
	if (Node == NULL)
	{
		List->First = NewNode;
		List->Last = NewNode;
		NewNode->Next = NULL;
		NewNode->Previous = NULL;
	}
	else
	{		
		NewNode->Next = Node->Next;
		NewNode->Previous = Node;
		Node->Next = NewNode;
		if (NewNode->Next != NULL)
			NewNode->Next->Previous = NewNode
		else
			List->Last = NewNode;
	}
	List->Count++;
}

void TLista_Remove(TList* List, TListNode* Node)
{
	TListNode* TempNode;
	
	TempNode = Node;
	if (Node->Next != NULL)
		Node->Next->Previous = Node->Previous;
	else
		List->Last = Node->Previous;
	if (Node->Previous != NULL)
		Node->Previous->Next = Node->Next;
	else
		List->First = Node->Next;
	free(TempNode);
	List->Count--;
}
