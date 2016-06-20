/*
**	TIPO ABSTRATO DE DADOS LISTA
**	DOUGLAS RODRIGUES DE ALMEIDA
**
**	Implementacao de lista como um vetor
*/

#include "core.h"
#include "list.h"

TLista* TLista_Criar(int Capacidade)
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
	NovaLista->Primeiro = -1;
	NovaLista->Tamanho = 0;
	NovaLista->Ultimo = -1;
  
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
	int novacapacidade;
	void** NovoItens;
	
	if (Lista->Tamanho >= Lista->Capacidade)
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
	Lista->Ultimo = Lista->Tamanho;
	Lista->Tamanho++;
	if (Lista->Tamanho == 1)
		Lista->Primeiro = 0;
	
	return true;
}

void TLista_Imprimir(TLista* Lista, TFuncaoImprimir FuncaoImprimir)
{
	TListaNo i;
	
	for (i = Lista->Primeiro; i <= Lista->Ultimo; i++)
		FuncaoImprimir(Lista->Itens[i]);
}

void* TLista_Item(TLista* Lista, const TListaNo Posicao)
{		
	return (Lista->Itens[Posicao]);
}

void TLista_Limpar(TLista* Lista, TFuncaoDestruir FuncaoDestruir)
{
	TListaNo i;
	
	for (i = 0; i < Lista->Tamanho; i++)
		FuncaoDestruir(&(Lista->Itens[i]));
	Lista->Primeiro = -1;
	Lista->Tamanho = 0;
	Lista->Ultimo = -1;
}

void TLista_Ordenar(TLista* Lista, TOrdem Ordem, TFuncaoComparar FuncaoComparar)
{
	
}

TListaNo TLista_Pesquisar(TLista* Lista, void* Item, TFuncaoIguais FuncaoIguais)
{
	TListaNo i;
	
	i = Lista->Primeiro;
	while (i <= Lista->Ultimo)
	{
		if (FuncaoIguais(Lista->Itens[i], Item))
			return i;
		i++;
	}
	
	return -1;
}

int TLista_Posicao(TLista* Lista, void* Item, TFuncaoIguais FuncaoIguais)
{
	return (TLista_Posicao(Lista, Item, FuncaoIguais) + 1);
}

void TLista_Remover(TLista* Lista, TListaNo No, TFuncaoDestruir FuncaoDestruir)
{
	TListaNo i;
	
	if (No > Lista->Ultimo)
		return;
	
	FuncaoDestruir(&(Lista->Itens[No]));
	for (i = No; i < Lista->Ultimo; i++)
		Lista->Itens[No] = Lista->Itens[No+1];
	Lista->Tamanho--;
	if (Lista->Tamanho == 0)
	{
		Lista->Primeiro = -1;
		Lista->Ultimo = -1;
	}
	else
		Lista->Ultimo = Lista->Tamanho -1;
}

int TLista_Tamanho(TLista* Lista)
{
	return Lista->Tamanho;
}

void TLista_Trocar(TLista* Lista, TListaNo NoA, TListaNo NoB)
{
	void* Item;
	
	Item = Lista->Itens[NoA];
	Lista->Itens[NoA] = Lista->Itens[NoB];
	Lista->Itens[NoB] = Item;
}
