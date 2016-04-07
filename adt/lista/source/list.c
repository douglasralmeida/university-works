//AEDS 2
//LIST ABSTRACT DATA TYPE
//DOUGLAS RODRIGUES DE ALMEIDA
//
//LinkedList ADT Implementation

#include "list.h"

TList* TList_Create(void)
{
	TList* TempList;
	
	TempList = (TList*)malloc(sizeof(TList));
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
	TList_Insert(List, Item, List->Last);
}

void TList_Clear(TList* List)
{
	TListNode* PreviousNode, TempNode;
	
	TempNode = List->Last;
	while (TempNode != NULL)
	{
		PreviousNode = TempNode->Previous;
		TList_Remove(List, TempNode);
		TempNode := PreviousNode;
	}
}

void TList_Exchange(TListNode* NodeA, TListNode* NodeB)
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

void TList_Remove(TList* List, TListNode* Node)
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
