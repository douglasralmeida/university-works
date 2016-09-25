/*
**	TAD MEMORIA
**	DOUGLAS RODRIGUES DE ALMEIDA
**
**	Implementação do simulador de memoria
*/

#include "memoria.h"

TMemoria* TMemoria_Criar(size_t Capacidade)
{
	size_t i;
	TMemoria* NovaMemoria;
	
	NovaMemoria = malloc(sizeof(TMemoria));
	if (!NovaMemoria)
		return NULL;
	NovaMemoria->Itens = malloc(Capacidade * sizeof(void*));
	if (!NovaMemoria->Itens)
	{
		free(NovaMemoria);
		return NULL;
	}
	NovaMemoria->Capacidade = Capacidade;
	for (i = 0; i < Capacidade; i++)
		NovaMemoria->Itens[i] = NULL;
	NovaMemoria->ItensCont = 0;
	NovaMemoria->Primeiro = 0;
	NovaMemoria->Ultimo = Capacidade - 1;

	return NovaMemoria;
}

void TMemoria_Destruir(TMemoria** PMemoria)
{
	free((*PMemoria)->Itens);
	free(*PMemoria);
	*PMemoria = NULL;
}

void TMemoria_Escrever(TMemoria* Memoria, void* Dado)
{
	Memoria->Ultimo++;
	if (Memoria->Ultimo == Memoria->Capacidade)
		Memoria->Ultimo = 0;
	Memoria->Itens[Memoria->Ultimo] = Dado;
	Memoria->ItensCont++;
}

void* TMemoria_LerPrimeiro(TMemoria* Memoria)
{
	void* Item;
	
	Item = Memoria->Itens[Memoria->Primeiro];
	Memoria->Itens[Memoria->Primeiro] = NULL;
	Memoria->Primeiro++;
	if (Memoria->Primeiro == Memoria->Capacidade)
		Memoria->Primeiro = 0;
	Memoria->ItensCont--;

	return Item;
}

void* TMemoria_LerUltimo(TMemoria* Memoria)
{
	void* Item;
	
	Item = Memoria->Itens[Memoria->Ultimo];
	Memoria->Itens[Memoria->Ultimo] = NULL;
	if (Memoria->Ultimo > 0)
		Memoria->Ultimo--;
	else
		Memoria->Ultimo = Memoria->Capacidade - 1;
	Memoria->ItensCont--;

	return Item;
}
