/*
**	TIPO ABSTRATO DE DADOS FILA
**	DOUGLAS RODRIGUES DE ALMEIDA
**
**	Implementação de fila com vetor
*/

#include <stdio.h>
#include <stdlib.h>
#include "fila.h"

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
	
	if (Fila->Frente == Fila->Tras)
	{
		printf("Erro (0x26): Erro ao desenfileirar. Fila vazia.\n");
		return NULL;
	}
	else
	{
		Item = Fila->Itens[Fila->Frente - 1];
		Fila->Frente = Fila->Frente % Fila->Capacidade + 1;
		return Item;
	}
}

bool TFila_Enfileirar(TFila* Fila, void* Item)
{
	if (Fila->Tras % Fila->Capacidade + 1 == Fila->Frente)
	{
		printf("Erro: (0x25): Erro ao enfileirar em fila cheia.\n");
		return false;
	}
	else 
	{
		Fila->Itens[Fila->Tras - 1] = Item;
		Fila->Tras = Fila->Tras % Fila->Capacidade + 1;
		return true;
	}
}

void TFila_Imprimir(TFila* Fila, TFuncaoImprimir FuncaoImprimir)
{
	TFilaNo NoTemp;
	
	if (Fila->Frente > Fila->Tras)
	{
		NoTemp = Fila->Frente;
		while (NoTemp <= Fila->Capacidade)
		{
			FuncaoImprimir(Fila->Itens[NoTemp - 1]);
			NoTemp++;
		}
		NoTemp = 1;
		while (NoTemp < Fila->Tras)
		{
			FuncaoImprimir(Fila->Itens[NoTemp - 1]);
			NoTemp++;
		}
	}
	else
	{
		NoTemp = Fila->Frente;
		while (NoTemp < Fila->Tras)
		{
			FuncaoImprimir(Fila->Itens[NoTemp - 1]);
			NoTemp++;
		}
	}
}

void TFila_Limpar(TFila* Fila, TFuncaoDestruir FuncaoDestruir)
{
	TFilaNo NoTemp;
	
	if (Fila->Frente > Fila->Tras)
	{
		NoTemp = Fila->Frente;
		while (NoTemp <= Fila->Capacidade)
		{
			FuncaoDestruir(&Fila->Itens[NoTemp - 1]);
			NoTemp++;
		}
		NoTemp = 1;
		while (NoTemp < Fila->Tras)
		{
			FuncaoDestruir(&Fila->Itens[NoTemp - 1]);
			NoTemp++;
		}
	}
	else
	{
		NoTemp = Fila->Frente;
		while (NoTemp < Fila->Tras)
		{
			FuncaoDestruir(&Fila->Itens[NoTemp-1]);
			NoTemp++;
		}
	}
	Fila->Frente = 1;
	Fila->Tras = 1;
}

size_t TFila_Tamanho(TFila* Fila)
{
	if (Fila->Frente > Fila->Tras)
		return Fila->Capacidade - Fila->Frente + Fila->Tras;
	else
		return Fila->Tras - Fila->Frente;
}
