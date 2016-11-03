/*
**	ANDANDO NA FÍSICA
**	DOUGLAS RODRIGUES DE ALMEIDA
**
**	Aplicativo principal
*/

#include <stdlib.h>
#include "mapa.h"

int main()
{
	TMapa* Mapa;
	
	Mapa = TMapa_Criar();
	if (!Mapa)
		exit(0);
	TMapa_ProcessarEntrada(Mapa);

	TMapa_Imprimir(Mapa);

	TMapa_Destruir(&Mapa);
	exit(EXIT_SUCCESS);
}
