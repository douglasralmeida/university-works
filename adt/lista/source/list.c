//AEDS 2
//LIST ABSTRACT DATA TYPE
//DOUGLAS RODRIGUES DE ALMEIDA
//
//LinkedList ADT Implementation

#include "list.h"

TList* TList_Create(void)
{
  TList* TempList = (TList*)malloc(sizeof(TList));
  TempList->Count = 0;
  TempList->First = NULL;
  TempList->Last = NULL;
  
  return TempList;
}

void TList_Destroy(TList** PList)
{
  free(*PList);
  PList = NULL;
}

void TList_Add(TList* List, TListItem Item)
{
	if (TList_IsEmpty(List))
	{
		TList_Insert(List, Item, NULL);
	}
	else
	{
		TList_Insert(List, Item, List->Last);
	}
}

void TList_Clear(TList* List)
{
  
}

void TList_Insert(TList* List, TListItem Item, TListNode* Node)
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
		List->Last = NewNode;
		NewNode->Next = Node->Next;
		NewNode->Previous = Node;
		Node->Next = NewNode;
	}
	List->Count++;
}

void TList_Remove(TList* List, int Position)
{
  
}
