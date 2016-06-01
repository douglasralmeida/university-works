/*
**	TIPO ABSTRATO DE DADOS FILA COM PRIORIDADES
**	DOUGLAS RODRIGUES DE ALMEIDA
**
**	Implementacao de fila com prioridades encadeada por ponteiros
*/

#include "filaprior.h"

void AjustarHeap(TFilaPrioridade* Fila)
{
	size_t i;
	size_t pai;
	TFilaItem TempItem;
	
	i = Fila->Tamanho;
	pai = i >> 1;
	while ((i > 1) && (Fila->FuncaoCompara(Fila->Heap[pai], Fila->Heap[i])))
	{
		TempItem = Fila->Heap[pai].Item;
		Fila->Heap[pai].Item = Fila->Heap[i].Item;
		Fila->Heap[i].Item = TempItem;
		i = pai;
		pai = i >> 1;
	}
}

void RefazerHeap(TFilaPrioridade)
{
	
}

TFilaPrioridade* TFilaPrioridade_Criar(size_t Capacidade, TFuncaoComparaPrioridade Funcao)
{
	TFilaPrioridade* NovaFila;
	
	NovaFila = (TFilaPrioridade*)malloc(sizeof(TFilaPrioridade));
	if (NovaFila == NULL)
	{
		printf("Erro (0x41): Erro durante alocacao de memoria.\n");
		return NULL;
	}
	NovaFila->Heap = (TFilaPrioridadeNo*)malloc((Capacidade + 1) * sizeof(TFilaPrioridade));
	if (NovaFila == NULL)
	{
		printf("Erro(0x44): Erro durante alocacao de memoria.\n");
		free(NovaFila);
		return NULL;
	}
	NovaFila->Capacidade = Capacidade;
	NovaFila->Expansao = 1024;
	NovaFila->FuncaoCompara = Funcao;
	NovaFila->Tamanho = 0;
  
	return NovaFila;
}

void TFilaPrioridade_Destruir(TFilaPrioridade** PFila)
{	
	if (PFila != NULL)
	{
		free((*PFila)->Heap);
		free(*PFila);
		PFila = NULL;
	}
}
*
void TFilaPrioridade_Desenfileirar(TFilaPrioridade* Fila, TItem* Item)
{
	if (Fila->Tamanho == 0)
	{
		printf("Erro (0x42): Erro ao desenfileirar. Fila vazia.\n");
	}
	else
	{
		*Item = Fila->Heap[1];
		Fila[1]->Item = Fila[Fila->Tamanho]->Item;
		Fila->Tamanho--;
		RefazHeap(Fila, 1);
	}
}

bool TFilaPrioridade_Enfileirar(TFilaPrioridade* Fila, const TListaItem Item)
{
	size_t novacapacidade;
	TFilaPrioridadeNo* NovoHeap;
	
	/* ops...fila cheia. Hora de alocar mais memoria */
	if (Fila->Tamanho >= Fila->Capacidade)
	{
		novacapacidade = Fila->Capacidade + Fila->Expansao;
		NovoHeap = realloc(Fila->Heap, sizeof(TFilaPrioridadeNo) * (novotamanho + 1));
		if (NovoHeap == NULL)
		{
			printf("Erro (0x45): Erro durante alocacao de memoria.\n");
			return false;
		}
		Fila->Heap = NovoHeap;
		Fila->Capacidade = novacapacidade;
	}
	/* inserindo item no heap */
	Fila->Heap[Fila->Tamanho].Item = Item;
	Fila->Tamanho++;
	AjustarFila(Fila);
	
	return true;
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

size_t TFilaPrioridade_Tamanho(TFilaPrioridade* Fila)
{
	return Fila->Tamanho;
}
