/*
**	TIPO ABSTRATO DE DADOS FILA COM PRIORIDADES
**	DOUGLAS RODRIGUES DE ALMEIDA
**
**	Implementacao de fila com prioridades encadeada por ponteiros
*/

#include "filaprior.h"

TFilaPrioridade* TFilaPrioridade_Criar(void)
{
	int i;
	TFilaPrioridade* NovaFila;
	
	NovaFila = (TFilaPrioridade*)malloc(sizeof(TFilaPrioridade);
	if (NovaFila == NULL)
	{
		printf("Erro (0x41): Erro durante alocacao de memoria.\n");
		return NULL;
	}
	NovaFila->Frente = NULL;
	NovaFila->Tamanho = 0;
  
	return NovaFila;
}

void TFilaPrioridade_Destruir(TFilaPrioridade** PFila)
{	
	if (PFila != NULL)
	{
		TFilaPrioridade_Limpar(*PFila);
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

void TFilaPrioridade_Enfileirar(TFilaPrioridade* Fila, const TListaItem Item)
{
	int i;
	TFilaNo* NoNovo;
	TFilaNo* NoAtual;
	
	NoNovo = (TFIlaNo*)malloc(sizeof(TFilaNo));
	if (NoNovo == NULL)
	{
		printf("Erro (0x43): Erro durante alocacao de memoria.\n");
		return;
	}
	NoNovo->Item = Item;
	NoNovo->Esquerda = NULL;
	NoNovo->Direita = NULL;
	/* Se a fila virtual estiver vazia */	
	if (TFilaPrioridade_Tamanho(Fila) == 0)
	{
		Fila->Frente = NovoNo;
	}
	else
	{
		NoAtual = Fila->Frente;
		if (TItem_Compara(Fila->Frente->Item, NoNovo->Item))
			
		else
			
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

size_t TFilaPrioridade_Tamanho(TFilaPrioridade* Fila)
{
	return Fila->Tamanho;
}
