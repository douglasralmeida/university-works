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
		exit(EXIT_FAILURE);
	if (TMapa_ProcessarEntrada(Mapa))
	{
		TMapa_EncontrarMenorCaminho(Mapa);
		TMapa_ImprimirResultado(Mapa);
	}
	TMapa_Destruir(&Mapa);
	exit(EXIT_SUCCESS);
}
