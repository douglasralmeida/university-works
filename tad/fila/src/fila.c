/*
**	TIPO ABSTRATO DE DADOS FILA
**	DOUGLAS RODRIGUES DE ALMEIDA
**
**	Implementacao de uma fila encadeada por ponteiros
*/

#include "fila.h"

TFila* TFila_Criar(TFuncaoDestruir FuncaoDestruir, TFuncaoImprimir FuncaoImprimir)
{
	TFila* NovaFila;
	
	NovaFila = (TFila*)malloc(sizeof(TFila));
	if (NovaFila == NULL)
	{
		printf("Erro (0x21): Erro durante alocacao de memoria.\n");
		return NULL;
	}
 	NovaFila->Frente = NULL;
	NovaFila->FuncaoDestruir = FuncaoDestruir;
	NovaFila->FuncaoImprimir = FuncaoImprimir;
  	NovaFila->Tamanho = 0;
	NovaFila->Tras = NULL;
	
	return NovaFila;
}

void TFila_Destruir(TFila** PFila)
{
	if (PFila != NULL)
	{
		TFila_Limpar(*PFila);
		free(*PFila);
		PFila = NULL;
	}
}

void* TFila_Desenfileirar(TFila* Fila)
{
	TFilaNo* NoTemp;
	void* Item;
	
	if (TFila_Tamanho(Fila) == 0)
	{
		printf("Erro (0x22): Fila vazia.\n");
		return NULL;
	}
	else
	{
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
	Fila->Tras = NoNovo;
	Fila->Tamanho++;
	
	return true;
}

void TFila_Imprimir(TFila* Fila)
{
	TFilaNo* NoTemp;

	NoTemp = Fila->Frente;
	while (NoTemp != NULL)
	{
		Fila->FuncaoImprimir(NoTemp->Item);
		NoTemp = NoTemp->Proximo;
	}
}

void TFila_Limpar(TFila* Fila)
{
	TFilaNo* NoProximo;
	TFilaNo* NoTemp;
	
	NoTemp = Fila->Frente;
	while (NoTemp != NULL)
	{
		NoProximo = NoTemp->Proximo;
		Fila->FuncaoDestruir(&(NoTemp->Item));
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