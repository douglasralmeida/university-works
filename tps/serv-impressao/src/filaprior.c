/*
**	TIPO ABSTRATO DE DADOS FILA COM PRIORIDADES
**	DOUGLAS RODRIGUES DE ALMEIDA
**
**	Implementacao de fila com prioridades encadeada por ponteiros
*/

#include "filaprior.h"

TFilaPrioridade* TFilaPrioridade_Criar(const unsigned int QuantTiposPrioridade)
{
	int i;
	TFilaPrioridade* NovaFila;
	
	NovaFila = (TFilaPrioridade*)malloc(sizeof(TFilaPrioridade);
	if (NovaFila == NULL)
	{
		printf("Erro (0x11): Erro durante alocacao de memoria.\n");
		return NULL;
	}
	NovaFila->FilasVirtuais = (TFilaVirtal*)malloc(QuantTiposPrioridade * sizeof(TFilaVirtal));
	if (NovaFila->FilasVirtuais == NULL)
	{
		printf("Erro (0x12): Erro durante alocacao de memoria.\n");
		free(NovaFila);
		return NULL;
	}
	for (i = 0; i < QuantTiposPrioridade; i++)
	{
		NovaFila->FilasVirtuais[i].Frente = NULL;
		NovaFila->FilasVirtuais[i].Tras = NULL;
	}
	NovaFila->TiposPrioridade = QuantTiposPrioridade;
 	NovaFila->Tamanho = 0;
  	NovaFila->Frente = NULL;
	NovaFila->Tras = NULL;
  
	return NovaFila;
}

void TFilaPrioridade_Destruir(TFilaPrioridade** PFila)
{
	TFilaNo* No;
	TFilaNo* NoTemp;	
	
	if (PFila != NULL)
	{
		No = (*PFila)->Frente;
		while (No != NULL)
		{
			NoTemp = No->Proximo;
			free(No);
			No = NoTemp;
		}
		free((*PFila)->FilasVirtuais);
		free(*PFila);
		PFila = NULL;
	}
}

TListaItem TFilaPrioridade_Desenfileirar(TFilaPrioridade* Fila)
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

void TFilaPrioridade_Enfileirar(TFilaPrioridade* Fila, const TListaItem Item, const unsigned int Prioridade)
{
	bool atras_todos;
	bool total_prioridade;
	int i;
	TFilaNo* NoNovo;
	
	if (Prioridade > Fila->TiposPrioridade)
	{
		printf("Erro (0x13): Prioridade informada nao suportada pela fila.\n");
		return;
	}
	NoNovo = (TFIlaNo*)malloc(sizeof(TFilaNo));
	if (NoNovo == NULL)
	{
		printf("Erro (0x12): Erro durante alocacao de memoria.\n");
		return;
	}
	NoNovo->Item = Item;
	
	if (Fila->FilaVirtual[Prioridade-1].Frente == NULL)
	{
		Fila->FilaVirtual[Prioridade-1].Frente = NoNovo;
		for (i = Prioridade - 2; i >= 0; i--)
			if (Fila->FilaVirtual[i].Tras != NULL)
			{
				Fila->FilaVirtual[i].Tras->Proximo = NoNovo;
				break;
			}
		if (Fila->Frente == NULL)
			Fila->Frente = NoNovo;
		else
		{
			total_prioridade = true;
			for (i = 0; i < Prioridade - 1; i++)
				if (Fila.Frente == Fila->FilaVirtual[i].Frente)
				{
					total_prioridade = false;
					break;
				}
			if (total_prioridade)
				Fila->Frente = NoNovo;
		}
	}

	if (Fila->FilaVirtual[Prioridade-1].Tras == NULL)
	{
		Fila->FilaVirtual[Prioridade-1].Tras = NoNovo;
		for (i = Prioridade; i < Fila->TiposPrioridade; i++)
			if (Fila->FilaVirtual[i].Frente != NULL)
			{
				NoNovo->Proximo = Fila->FilaVirtual[i].Frente;
				break;
			}
		atras_todos = true;
		for (i = Prioridade; i < Fila->TiposPrioridade; i++)
		{
			if (Fila->Tras == Fila->FilaVirtual[i].Tras)
			{
				atras_todos = false;
				break;
			}
		}
		if ((atras_todos) || (Fila->Tras == NULL))
			Fila->Tras = NoNovo;
	}
	else
	{
		if (Fila->Tras == Fila-FilaVirtual[Prioridade-1].Tras)
			Fila->Tras = NoNovo;
		NoNovo->Proximo = Fila->FilaVirtual[Prioridade-1].Tras->Proximo;
		Fila->FilaVirtual[Prioridade-1].Tras->Proximo = NoNovo;
		Fila->FilaVirtual[Prioridade-1].Tras = NoNovo;
	}
	Lista->Tamanho++;
}

void TFilaPrioridade_Imprimir(TFilaPrioridade* Fila)
{
	TFilaNo* NoTemp;

	NoTemp = Fila->Frente;
	while (NoTemp != NULL)
	{
		TFilaItem_Imprimir(&(NoTemp->Item));
		NoTemp = NoTemp->Proximo;
	}
}

void TFilaPrioridade_Limpar(TFilaPrioridade* Fila)
{
	int i;
	TFilaNo* NoProximo;
	TFilaNo* NoTemp;
	
	NoTemp = Fila->Frente;
	while (NoTemp != NULL)
	{
		NoProximo = NoTemp->Proximo;
		free(NoTemp);
		NoTemp = NoProximo;
	}
	for (i = 0; i < Fila-TiposPrioridade; i++)
	{
		Fila->FilasVirtuais[i].Frente = NULL;
		Fila->FilasVirtuais[i].Tras = NULL;
	}
	Fila->Tamanho = 0;
	Fila->Tras = NULL;
}

unsigned int TFilaPrioridade_Tamanho(TFilaPrioridade* Fila)
{
	return Fila->Tamanho;
}