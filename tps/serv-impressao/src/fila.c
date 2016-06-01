/*
**	TIPO ABSTRATO DE DADOS FILA
**	DOUGLAS RODRIGUES DE ALMEIDA
**
**	Implementacao de uma fila encadeada por ponteiros
*/

#include "fila.h"

TFila* TFila_Criar(void)
{
	int i;
	TFila* NovaFila;
	
	NovaFila = (TFila*)malloc(sizeof(TFila);
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

void TFila_Destruir(TFila** PFila)
{
	TFilaNo* No;
	TFilaNo* NoTemp;	
	
	if (PFila != NULL)
	{
		TFila_Limpar(*PFila);
		free(*PFila);
		PFila = NULL;
	}
}

void TFila_Desenfileirar(TFila* Fila, TItem* Item)
{
	TFilaNo* NoTemp;
	
	if (TFila_Tamanho(Fila) == 0)
	{
		printf("Erro (0x22): Fila vazia.\n");
	}
	else
	{
		NoTemp = Fila->Frente;
		*Item = NoTemp->Item;
		Fila->Frente = Fila->Frente->Prox;
		Fila->Tamanho--;
	}
}

void TFila_Enfileirar(TFila* Fila, const TListaItem Item)
{
	TFilaNo* NoNovo;
	
	NoNovo = (TFilaNo*)malloc(sizeof(TFilaNo));
	if (NoNovo == NULL)
	{
		printf("Erro (0x23): Erro durante alocacao de memoria.\n");
		return;
	}
	NoNovo->Item = Item;
	NoNovo->Proximo = NULL;
	Fila->Ultimo->Prox = NoNovo;
	Fila->Ultimo = NoNovo;
	Fila->Tamanho++;
}

void TFila_Imprimir(TFila* Fila)
{
	TFilaNo* NoTemp;

	NoTemp = Fila->Frente;
	while (NoTemp != NULL)
	{
		TItem_Imprimir(&(NoTemp->Item));
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
		free(NoTemp);
		NoTemp = NoProximo;
	}
	Fila->Tamanho = 0;
}

size_t TFila_Tamanho(TFila* Fila)
{
	return Fila->Tamanho;
}
