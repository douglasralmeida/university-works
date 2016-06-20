/*
**	TIPO ABSTRATO DE DADOS LISTA
**	DOUGLAS RODRIGUES DE ALMEIDA
**
**	Implementacao de lista como um vetor
*/

#include "list.h"

TLista* TLista_Criar(size_t Capacidade)
{
	TLista* NovaLista;
	
	NovaLista = (TLista*)malloc(sizeof(TLista));
	if (NovaLista == NULL)
	{
		printf("Erro (0x11): Erro durante alocacao de memoria.\n");
		return NULL;
	}
	NovaLista->Itens = malloc(Capacidade * sizeof(void*));
	if (NovaLista->Itens == NULL)
	{
		printf("Erro(0x12): Erro durante alocacao de memoria.\n");
		free(NovaLista);
		return NULL;
	}
	NovaLista->Capacidade = Capacidade;
	NovaLista->Expansao = LISTA_EXPANSAO;
	NovaLista->Tamanho = 0;
  
	return NovaLista;
}

void TLista_Destruir(TLista** PLista, TFuncaoDestruir FuncaoDestruir)
{
	if (PLista != NULL)
	{
		TLista_Limpar(*PLista, FuncaoDestruir);
		free((*PLista)->Itens);
		free(*PLista);
		PLista = NULL;
	}
}

bool TLista_Adicionar(TLista* Lista, void* Item)
{
	size_t novacapacidade;
	void** NovoItens;
	
	if (Fila->Tamanho >= Fila->Capacidade)
	{
		novacapacidade = Lista->Capacidade + Lista->Expansao;
		NovoItens = realloc(Lista->Itens, novacapacidade * sizeof(void*));
		if (NovoItens == NULL)
		{
			printf("Erro (0x14): Erro durante alocacao de memoria.\n");
			return false;
		}
		Lista->Itens = NovoItens;
		Lista->Capacidade = novacapacidade;
	}
	Lista->Itens[Lista->Tamanho] = Item;
	Lista->Tamanho++;
	
	return true;
}

void TLista_Imprimir(TLista* Lista, TFuncaoImprimir FuncaoImprimir)
{
	int i;
	
	for (i = 0; i < Lista->Tamanho; i++)
		FuncaoImprimir(NoTemp->Item[i]);
}

void* TLista_Item(TLista* Lista, const size_t Posicao)
{	
	if (Posicao == 0)
		return NULL;
	
	return Lista->Item[Posicao-1];
}

void TLista_Limpar(TLista* Lista, TFuncaoDestruir FuncaoDestruir)
{
	size_t i;
	
	for (i = 0; i < Lista->Tamanho; i++)
		FuncaoDestruir(&(Fila->Itens[i]));
	Lista->Tamanho = 0;
}

void TLista_Ordenar(TLista* Lista, TListaOrdem Ordem, TFuncaoComparar FuncaoComparar)
{
	
}

TListaNo TLista_Pesquisar(TLista* Lista, void* Item, TFuncaoIguais FuncaoIguais)
{
	TListaNo i;
	
	i = 0;
	while (i < Lista->Tamanho)
	{
		if (FuncaoIguais(Lista->Itens[i], Item))
			return i;
		i++;
	}
	
	return -1;
}

size_t TLista_Posicao(TLista* Lista, void* Item, TFuncaoIguais FuncaoIguais)
{
	return (TLista_Posicao(Lista, Item, FuncaoIguais) + 1);
}

void TLista_Remover(TLista* Lista, TListaNo No, TFuncaoDestruir FuncaoDestruir)
{
	TListaNo i;
	
	if (No >= Lista->Tamanho)
		return
	
	FuncaoDestruir(&(No->Item));
	for (i = No; i < Lista->Tamanho - 1; i++)
		Lista->Item[No]->Item = Lista->Item[No+1]->Item;
	Lista->Tamanho--;
}

size_t TLista_Tamanho(TLista* Lista)
{
	return Lista->Tamanho;
}

void TLista_Trocar(TLista Lista, TListaNo NoA, TListaNo NoB)
{
	void* Item;
	
	Item = Lista->Item[NoA];
	Lista->Item[NoA] = Lista->Item[NoB];
	Lista->->Item[NoB] = Item;
}