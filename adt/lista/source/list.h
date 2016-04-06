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

TList* TList_Create(void);
void TList_Destroy(TList** PList);
void TList_Add(TList* List, int Value);
void TList_Clear(TList* List);
void TList_Insert(TList* List, int Value, int Position);
void TList_Remove(TList* List, int Position);

#endif
