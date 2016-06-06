/*
**	TIPO ABSTRATO DE DADOS LISTA
**	DOUGLAS RODRIGUES DE ALMEIDA
**
**	Implementacao de lista duplamente encadeada por ponteiros
*/

#include "list.h"

TLista* TLista_Criar(TFuncaoDestruir FuncaoDestruir, TFuncaoIguais FuncaoIguais, TFuncaoImprimir FuncaoImprimir)
{
	TLista* NovaLista;
	
	NovaLista = (TLista*)malloc(sizeof(TLista));
	if (NovaLista == NULL)
	{
		printf("Erro (0x11): Erro durante alocacao de memoria.\n");
		return NULL;
	}
	NovaLista->FuncaoDestruir = FuncaoDestruir;
	NovaLista->FuncaoIguais = FuncaoIguais;
	NovaLista->FuncaoImprimir = FuncaoImprimir;
 	NovaLista->Tamanho = 0;
  	NovaLista->Primeiro = NULL;
	NovaLista->Ultimo = NULL;
  
	return NovaLista;
}

void TLista_Destruir(TLista** PLista)
{
	if (PLista != NULL)
	{
		TLista_Limpar(*PLista);
		free(*PLista);
		PLista = NULL;
	}
}

bool TLista_Adicionar(TLista* Lista, void* Item)
{
	return TLista_Inserir(Lista, Item, Lista->Ultimo);
}

bool TLista_EstaVazia(TLista* Lista)
{
	return (Lista->Primeiro == NULL);
}

void TLista_Imprimir(TLista* Lista)
{
	TListaNo* NoTemp;

	NoTemp = Lista->Primeiro;
	while (NoTemp != NULL)
	{
		Lista->FuncaoImprimir(NoTemp->Item);
		NoTemp = NoTemp->Proximo;
	}
}

bool TLista_Inserir(TLista* Lista, void* Item, TListaNo* No)
{
	TListaNo* NoNovo;
	
	NoNovo = (TListaNo*)malloc(sizeof(TListaNo));
	if (NoNovo == NULL)
	{
		printf("Erro (0x12): Erro durante alocacao de memoria.\n");
		return false;
	}
	NoNovo->Item = Item;
	if (No == NULL)
	{
		if (TLista_EstaVazia(Lista))
		{
			Lista->Ultimo = NoNovo;
			NoNovo->Proximo = NULL;			
		}
		else
		{
			NoNovo->Proximo = Lista->Primeiro;
			Lista->Primeiro->Anterior = NoNovo;			
		}
		Lista->Primeiro = NoNovo;
		NoNovo->Anterior = NULL;
	}
	else
	{		
		NoNovo->Proximo = No->Proximo;
		NoNovo->Anterior = No;
		No->Proximo = NoNovo;
		if (NoNovo->Proximo != NULL)
			NoNovo->Proximo->Anterior = NoNovo;
		else
			Lista->Ultimo = NoNovo;
	}
	Lista->Tamanho++;
	return true;
}

void* TLista_Item(TLista* Lista, const size_t Posicao)
{
	size_t i;
	TListaNo* NoTemp;
	
	if (Posicao == 0)
		return NULL;
	
	NoTemp = Lista->Primeiro;
	for (i = 0; i < Posicao - 1; i++)
		NoTemp = NoTemp->Proximo;

	return NoTemp->Item;
}

void TLista_Limpar(TLista* Lista)
{
	TListaNo* NoAnterior; 
	TListaNo* NoTemp;
	
	NoTemp = Lista->Ultimo;
	while (NoTemp != NULL)
	{
		NoAnterior = NoTemp->Anterior;
		Lista->FuncaoDestruir(&(NoTemp->Item));
		free(NoTemp);
		NoTemp = NoAnterior;
	}
	Lista->Tamanho = 0;
	Lista->Primeiro = NULL;
	Lista->Ultimo = NULL;
}

size_t TLista_Posicao(TLista* Lista, void* Item)
{
	size_t resultado;
	TListaNo* NoTemp;
	
	resultado = 0;
	NoTemp = Lista->Primeiro;
	while (NoTemp != NULL)
	{
		resultado++;
		if (Lista->FuncaoIguais(NoTemp->Item, Item))
			return resultado;
		NoTemp = NoTemp->Proximo;
	}
	return 0;
}

void TLista_Remover(TLista* Lista, TListaNo* No)
{
	TListaNo* NoTemp;
	
	NoTemp = No;
	if (No->Proximo != NULL)
		No->Proximo->Anterior = No->Anterior;
	else
		Lista->Ultimo = No->Anterior;
	if (No->Anterior != NULL)
		No->Anterior->Proximo = No->Proximo;
	else
		Lista->Primeiro = No->Proximo;
	free(NoTemp);
	Lista->Tamanho--;
}

size_t TLista_Tamanho(TLista* Lista)
{
	return Lista->Tamanho;
}

void TLista_Trocar(TListaNo* NoA, TListaNo* NoB)
{
	void* Item;
	
	Item = NoA->Item;
	NoA->Item = NoB->Item;
	NoB->Item = Item;
}
