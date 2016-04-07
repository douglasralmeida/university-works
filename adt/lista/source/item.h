//AEDS 2
//LIST ABSTRACT DATA TYPE
//DOUGLAS RODRIGUES DE ALMEIDA
//
//List ADT ListItem Implementation

#ifndef ITEM_H
#define ITEM_H

typedef struct _TListItem {
	int Value;
} TListItem;

//Create an item
TListItem* TListItem_Create(int Value);

//Destroy the item
void TList_Destroy(TListItem** PListItem);

#endif
