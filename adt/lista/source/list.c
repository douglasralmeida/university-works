//AEDS 2
//LIST ABSTRACT DATA TYPE
//DOUGLAS RODRIGUES DE ALMEIDA
//
//LinkedList ADT Implementation

#include "list.h"

TList* TList_Create(void)
{
  TList* TempList = (TList*)malloc(sizeof(TList));
  TempList->First = NULL;
  TempList->Last = NULL;
  
  return TempList;
}

void TList_Destroy(TList** PList)
{
  free(*PList);
  PList = NULL;
}

void TList_Add(TList* List, int Value)
{
  
}

void TList_Clear(TList* List)
{
  
}

void TList_Insert(TList* List, int Value, int Position)
{
  
}

void TList_Remove(TList* List, int Position)
{
  
}
