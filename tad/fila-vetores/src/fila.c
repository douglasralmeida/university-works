/*
**	TIPO ABSTRATO DE DADOS FILA
**	DOUGLAS RODRIGUES DE ALMEIDA
**
**	Implementação de fila com vetor
*/

#include <stdio.h>
#include "filaprior.h"



TFila* TFila_Criar(size_t Capacidade)
{
	TFila* NovaFila;
	
	NovaFila = (TFila*)malloc(sizeof(TFila));
	if (NovaFila == NULL)
	{
		printf("Erro (0x21): Erro durante alocacao de memoria.\n");
		return NULL;
	}
	NovaFila->Itens = malloc((Capacidade) * sizeof(void*));
	if (NovaFila->Itens == NULL)
	{
		printf("Erro(0x24): Erro durante alocacao de memoria.\n");
		free(NovaFila);
		return NULL;
	}
	NovaFila->Capacidade = Capacidade;
	NovaFila->Expansao = FILA_EXPANSAO;
	NovaFila->Frente = 1;
	NovaFila->Tras = 1;
	NovaFila->Tamanho = 0;
  
	return NovaFila;

}

void TFila_Destruir(TFila** PFila, TFuncaoDestruir FuncaoDestruir)
{
	if (PFila != NULL)
	{
		TFila_Limpar(*PFila, FuncaoDestruir);
		free((*PFila)->Itens);
		free(*PFila);
		*PFila = NULL;
	}
}

void* TFila_Desenfileirar(TFila* Fila)
{
	void* Item;
	
	if (TFila_Tamanho(Fila) == 0)
	{
		printf("Erro (0x26): Erro ao desenfileirar. Fila vazia.\n");
		return NULL;
	}
	else
	{
		Item = Fila->Item[Fila->Frente];
		Fila->Frente = Fila->Frente % Fila->Capacidade + 1;
	}
}

bool TFila_Enfileirar(TFila* Fila, void* Item)
{
	if (Fila->Tras % Fila->Capacidade + 1 == Fila->Frente)
		printf("Erro: (0x25): Erro ao enfileirar em fila cheia.\n");
	else 
	{
		Fila->Item[Fila->Tras] = Item;
		Fila->Tras = Fila->Tras % Fila->Capacidade + 1;
	}
}

void TFila_Imprimir(TFila* Fila, TFuncaoImprimir FuncaoImprimir)
{
	TFilaNo NoTemp;
	
	NoTemp = Fila->Frente;
	while (NoTemp <= Fila->Tras)
	{
		FuncaoImprimir(Fila->Itens[NoTemp]);
		NoTemp++;
	}
}

void TFila_Limpar(TFila* Fila, TFuncaoDestruir FuncaoDestruir)
{
	size_t i;
	
	for(i = 0; i <= Fila->Tamanho; i++)
		FuncaoDestruir(&(Fila->Item[i]));
	Fila->Tamanho = 0;
	NovaFila->Frente = 1;
	NovaFila->Tras = 1;
}

size_t TFila_Tamanho(TFila* Fila)
{
	return Fila->Tras % Fila->Capacidade - Fila->Frente % Fila->Capacidade;***(corrigir)
}
