/*
**	BIBLIOTECA DO FILIPE
**	DOUGLAS RODRIGUES DE ALMEIDA
**
**	Implementação do simulador de memoria
*/

#include "memoria.h"

TMemoria* TMemoria_Criar(size_t Tamanho)
{
	size_t i;
	TMemoria* NovaMemoria;
	
	NovaMemoria = malloc(sizeof(NovaMemoria));
	if (!NovaMemoria)
		return NULL;
	NovaMemoria->Itens = malloc(Tamanho * sizeof(void*));
	if (!NovaMemoria->Itens)
	{
		free(NovaMemoria);
		return NULL;
	}
	for (i = 0; i < Tamanho; i++)
		NovaMemoria->Itens[i] = NULL;
	NovaMemoria->Tamanho = Tamanho;

	return NovaMemoria;
}

void TMemoria_Destruir(TMemoria** PMemoria)
{
	free((*PMemoria)->Itens);
	free(*PMemoria);
	PMemoria = NULL	
}

void TMemoria_Escrever(TMemoria* Memoria, size_t Posicao, void* Dado)
{
	Memoria->Itens[Posicao] = Dado;
}

void* TMemoria_Ler(TMemoria* Memoria, size_t Posicao)
{
	return Memoria->Itens[Posicao];
}
