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
	void* TempItem;
	
	i = Fila->Tamanho;
	pai = i >> 1;
	while ((i > 1) && (Fila->FuncaoComparar(Fila->Heap[pai], Fila->Heap[i])))
	{
		TempItem = Fila->Heap[pai];
		Fila->Heap[pai] = Fila->Heap[i];
		Fila->Heap[i] = TempItem;
		i = pai;
		pai = i >> 1;
	}
}

void RefazerHeap(TFilaPrioridade* Fila, size_t n)
{
	
}

TFilaPrioridade* TFilaPrioridade_Criar(size_t Capacidade, TFuncaoComparar FuncaoComparar, TFuncaoDestruir FuncaoDestruir, TFuncaoImprimir FuncaoImprimir)
{
	TFilaPrioridade* NovaFila;
	
	NovaFila = (TFilaPrioridade*)malloc(sizeof(TFilaPrioridade));
	if (NovaFila == NULL)
	{
		printf("Erro (0x41): Erro durante alocacao de memoria.\n");
		return NULL;
	}
	NovaFila->Heap = malloc((Capacidade + 1) * sizeof(void*));
	if (NovaFila == NULL)
	{
		printf("Erro(0x44): Erro durante alocacao de memoria.\n");
		free(NovaFila);
		return NULL;
	}
	NovaFila->Capacidade = Capacidade;
	NovaFila->Expansao = 1024;
	NovaFila->FuncaoComparar = FuncaoComparar;
	NovaFila->FuncaoImprimir = FuncaoImprimir;
	NovaFila->FuncaoDestruir = FuncaoDestruir;
	NovaFila->Tamanho = 0;
  
	return NovaFila;
}

void TFilaPrioridade_Destruir(TFilaPrioridade** PFila)
{	
	if (PFila != NULL)
	{
		TFilaPrioridade_Limpar(*PFila);
		free((*PFila)->Heap);
		free(*PFila);
		PFila = NULL;
	}
}

void* TFilaPrioridade_Desenfileirar(TFilaPrioridade* Fila)
{
	void* Item;
	if (Fila->Tamanho == 0)
	{
		printf("Erro (0x42): Erro ao desenfileirar. Fila vazia.\n");
		return NULL;
	}
	else
	{
		Item = Fila->Heap[1];
		Fila->Tamanho--;
		RefazerHeap(Fila, 1);
		return Item;
	}
}

bool TFilaPrioridade_Enfileirar(TFilaPrioridade* Fila, void* Item)
{
	size_t novacapacidade;
	void* NovoHeap;
	
	/* ops...fila cheia. Hora de alocar mais memoria */
	if (Fila->Tamanho >= Fila->Capacidade)
	{
		novacapacidade = Fila->Capacidade + Fila->Expansao;
		NovoHeap = realloc(Fila->Heap, (novacapacidade + 1) * sizeof(void*));
		if (NovoHeap == NULL)
		{
			printf("Erro (0x45): Erro durante alocacao de memoria.\n");
			return false;
		}
		Fila->Heap = NovoHeap;
		Fila->Capacidade = novacapacidade;
	}
	/* inserindo item no heap */
	Fila->Tamanho++;
	Fila->Heap[Fila->Tamanho] = Item;
	AjustarHeap(Fila);
	
	return true;
}

void TFilaPrioridade_Imprimir(TFilaPrioridade* Fila)
{
	/* */
}

void TFilaPrioridade_Limpar(TFilaPrioridade* Fila)
{
	size_t i;
	
	for(i = 1; i <= Fila->Tamanho; i++)
	{
			Fila->FuncaoDestruir(&(Fila->Heap[i]));
	}
	Fila->Tamanho = 0;
}

size_t TFilaPrioridade_Tamanho(TFilaPrioridade* Fila)
{
	return Fila->Tamanho;
}
