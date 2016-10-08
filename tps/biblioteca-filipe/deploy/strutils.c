/*
**	BIBLIOTECA DO FILIPE
**	DOUGLAS RODRIGUES DE ALMEIDA
**
**	Implementação das consultas do sistema
*/

#include "strutils.h"
#include <string.h>

bool StrComparar(void* String1, void* String2)
{
	return (strcmp((const char*)String1, (const char*)String2) < 0);
}
