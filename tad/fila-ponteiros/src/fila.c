/*
**	TIPO ABSTRATO DE DADOS FILA
**	DOUGLAS RODRIGUES DE ALMEIDA
**
**	Implementacao de uma fila encadeada por ponteiros
*/

#include <stdio.h>
#include <stdlib.h>
#include "fila.h"

TFila* TFila_Criar()
{
	TFila* NovaFila;
	
	NovaFila = (TFila*)malloc(sizeof(TFila));
	if (NovaFila == NULL)
	{
		printf("Erro (0x21): Erro durante alocacao de memoria.\n");
		return NULL;
	}
 	NovaFila->Frente = NULL;
  	NovaFila->Tamanho = 0;
	NovaFila->Tras = NULL;
	
	return NovaFila;
}

void TFila_Destruir(TFila** PFila, TFuncaoDestruir FuncaoDestruir)
{
	if (PFila != NULL)
	{
		
		TFila_Limpar(*PFila, FuncaoDestruir);
		free(*PFila);
		PFila = NULL;
	}
}

void* TFila_Desenfileirar(TFila* Fila)
{
	TFilaNo* NoTemp;
	void* Item;

	/*-- fila vazia? --*/		
	if (TFila_Tamanho(Fila) == 0)
	{
		printf("Erro (0x22): Fila vazia.\n");
		return NULL;
	}
	else
	{
		/*-- tira o primeiro item pra fora --*/	
		NoTemp = Fila->Frente;
		Item = NoTemp->Item;
		Fila->Frente = Fila->Frente->Proximo;
		free(NoTemp);
		Fila->Tamanho--;
		return Item;
	}
}

bool TFila_Enfileirar(TFila* Fila, void* Item)
{
	TFilaNo* NoNovo;
	
	NoNovo = (TFilaNo*)malloc(sizeof(TFilaNo));
	if (NoNovo == NULL)
	{
		printf("Erro (0x23): Erro durante alocacao de memoria.\n");
		return false;
	}
	NoNovo->Item = Item;
	NoNovo->Proximo = NULL;
	if (Fila->Frente == NULL)
		Fila->Frente = NoNovo;
	else
		Fila->Tras->Proximo = NoNovo;
	/*-- novos itens sempre irao para o final da fila --*/	
	Fila->Tras = NoNovo;
	Fila->Tamanho++;
	
	return true;
}

void TFila_Imprimir(TFila* Fila, TFuncaoImprimir FuncaoImprimir)
{
	TFilaNo* NoTemp;

	NoTemp = Fila->Frente;
	while (NoTemp != NULL)
	{
		FuncaoImprimir(NoTemp->Item);
		NoTemp = NoTemp->Proximo;
	}
}

void TFila_Limpar(TFila* Fila, TFuncaoDestruir FuncaoDestruir)
{
	TFilaNo* NoProximo;
	TFilaNo* NoTemp;
	
	NoTemp = Fila->Frente;
	/*-- varre a fila e destroi tudo --*/
	while (NoTemp != NULL)
	{
		NoProximo = NoTemp->Proximo;
		FuncaoDestruir(&(NoTemp->Item));
		free(NoTemp);
		NoTemp = NoProximo;
	}
	Fila->Frente = NULL;
	Fila->Tras = NULL;
	Fila->Tamanho = 0;
}

size_t TFila_Tamanho(TFila* Fila)
{
	return Fila->Tamanho;
}
