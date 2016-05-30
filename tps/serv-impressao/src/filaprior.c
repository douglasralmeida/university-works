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
	int i;
	TFilaNo* NoTemp;
	
	NoTemp = Fila->Frente;
	if (NoTemp == NULL)
	{
		printf("Erro (0x14): Fila vazia.\n");
		return;
	}
	else
	{
		if (NoTemp->Proximo != NULL)
		{
			i = 1;
			while (i < Fila->TipoPrioridades)
			{
				if (Fila->FilaVirtual[i].Frente == NoTemp->Proximo)
					break;
				i++;	
			}
			if (i < Fila->TipoPrioridades)
			{
				FilaVirtual[i-1].Frente = NULL;
				FilaVirtual[i-1].Tras = NULL;
			}
		}
	}

	free(NoTemp);
	Lista->Tamanho--;
}

bool TFilaVirtual_Vazia(TFilaVirtual* Fila)
{
	return (Fila->Frente = NULL);
}

void TFilaPrioridade_Enfileirar(TFilaPrioridade* Fila, const TListaItem Item, const unsigned int Prioridade)
{
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
	NoNovo->Proximo = NULL;
	/* Se a fila virtual estiver vazia */	
	if TFilaVirtual_Vazia(Fila->FilaVirtual + Prioridade - 1)
	{
		Fila->FilaVirtual[Prioridade-1].Frente = NoNovo;
		Fila->FilaVirtual[Prioridade-1].Tras = NoNovo;
		/* Checa a existencia de filas virtuais com prioridade maior que a prioridade informada */
		i = Prioridade - 2;
		while (i >= 0)
		{
			if (!TFilaVirtual_Vazia(Fila->FilaVirtual + i))
				break;
			i--;
		}
		if (i >= 0)
		{
			NoNovo->Proximo = Fila->FilaVirtual[i].Tras->Proximo;
			Fila->FilaVirtual[i].Tras->Proximo = NoNovo;
		}
		else
		{
			Fila->Frente = NoNovo;
			i = Prioridade;
			while (i < Fila->TiposPrioridade)
			{
				if (!TFilaVirtual_Vazia(Fila->FilaVirtual + i))
					break;
				i++;
			}
			if (i < Fila->TiposPrioridade)
				NoNovo->Proximo = Fila->FilaVirtual[i].Frente;
		}
	}
	else
	{
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
}

unsigned int TFilaPrioridade_Tamanho(TFilaPrioridade* Fila)
{
	return Fila->Tamanho;
}
