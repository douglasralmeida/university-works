//AEDS 2
//LIST ABSTRACT DATA TYPE
//DOUGLAS RODRIGUES DE ALMEIDA
//
//LinkedList ADT Test

#include <stdlib>
#include "item.h"
#include "list.h"

int main(void)
{
	TList* MyList = TList_Create();
	TList_Add(MyList, TListItem_Create(0));
	TList_Add(MyList, TListItem_Create(1));
	TList_Add(MyList, TListItem_Create(2));
	TList_Clear(MyList);	
	TList_Destroy(&MyList);
	
	exit(EXIT_SUCCESS);
}
