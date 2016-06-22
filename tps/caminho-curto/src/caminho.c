#include <stdlib.h>
#include "caminho.h"

TCaminho* TCaminho_Criar(int Origem, int Destino, int TempoMedio)
{
	TCaminho* NovoCaminho;

	NovoCaminho = (TCaminho*)malloc(sizeof(TCaminho));
	if (NovoCaminho != NULL)
	{
		NovoCaminho->Origem = Origem;
		NovoCaminho->Destino = Destino;
		NovoCaminho->TempoMedio = TempoMedio;
	}

	return NovoCaminho;
}

void TCaminho_Destruir(void** PCaminho)
{
	free(*PCaminho);
	PCaminho = NULL;
}
