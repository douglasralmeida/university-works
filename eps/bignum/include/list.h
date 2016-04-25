//AEDS 2
//LIST ABSTRACT DATA TYPE
//DOUGLAS RODRIGUES DE ALMEIDA
//
//List ADT Header

#ifndef LIST_H
#define LIST_H

typedef struct _TListNode {
	TListItem Item;
	TListNode* Previous;
	TListNode* Next;
} TListNode;

typedef struct _TList {
	TListNode* First;
	TListNode* Last;
} TList;

//Create an empty list
TList* TList_Create(void);

//Destroy the list
void TList_Destroy(TList** PList);

//Add an item to the list at end
void TList_Add(TList* List, TListItem Item);

//Remove all list items
void TList_Clear(TList* List);

//Swap position of two list itens
void TList_Exchange(TListNode* NodeA, TListNode* NodeB);

//Add an item after the list node
void TList_Insert(TList* List, TListItem Item, TListNode* Node);

//Remove the item of the list
void TList_Remove(TList* List, TListNode* Node);

#endif
