//AEDS 2
//LIST ABSTRACT DATA TYPE
//DOUGLAS RODRIGUES DE ALMEIDA
//
//LinkedList ADT ListItem Implementation

#include "item.h"

TListItem TListItem_Create(int Value)
{
	TListItem* TempItem;
	
	TempItem = (TListItem*)malloc(sizeof(TListItem));
 	TempItem->Value = Value;
  
	return TempItem;
}
