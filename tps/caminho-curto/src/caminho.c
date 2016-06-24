#include <stdlib.h>
#include "boolutils.h"
#include "caminho.h"

TCaminho* TCaminho_Criar(unsigned int Origem, unsigned int Destino, unsigned int TempoMedio)
{
	TCaminho* NovoCaminho;

	NovoCaminho = (TCaminho*)malloc(sizeof(TCaminho));
	if (NovoCaminho != NULL)
	{
		NovoCaminho->Origem = Origem;
		NovoCaminho->Destino = Destino;
		NovoCaminho->TempoMedio = TempoMedio;
		NovoCaminho->Visitado = false;
	}

	return NovoCaminho;
}

void TCaminho_Destruir(void** PCaminho)
{
	free(*PCaminho);
	PCaminho = NULL;
}

bool TCaminho_Comparar(void* PCaminho1, void* PCaminho2)
{
	TCaminho* Caminho1;
	TCaminho* Caminho2;
	
	Caminho1 = (TCaminho*)PCaminho1;
	Caminho2 = (TCaminho*)PCaminho2;
	return (Caminho1->TempoMedio > Caminho2->TempoMedio);
}