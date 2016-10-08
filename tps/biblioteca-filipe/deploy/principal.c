/*
**	BIBLIOTECA DO FILIPE
**	DOUGLAS RODRIGUES DE ALMEIDA
**
**	Aplicativo principal
*/

#include <stdlib.h>
#include "sistema.h"

int main()
{
	TSistema* Sistema;

	Sistema = TSistema_Criar();
	if (!Sistema)
		exit(EXIT_FAILURE);
	if (TSistema_ReceberEntrada(Sistema))
	{
		TSistema_Simular(Sistema);
		TSistema_Destruir(&Sistema);
		exit(EXIT_SUCCESS);
	}
	else
	{
		TSistema_Destruir(&Sistema);
		exit(EXIT_FAILURE);
	}
	
}
