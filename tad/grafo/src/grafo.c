/*
**	TIPO ABSTRATO DE DADOS GRAFO
**	DOUGLAS RODRIGUES DE ALMEIDA
**
**	Implementacao de grafo com listas de adjacencias usando ponteiros
*/

#include "grafo.h"

TGrafo* TGrafo_Criar(size_t NumVertices)
{
	int i, j;	
	TGrafo* NovoGrafo;
	TLista* NovaLista;
		
	NovoGrafo = (TGrafo*)malloc(sizeof(TGrafo));
	if (NovoGrafo == NULL)
	{
		printf("Erro (0x50). Erro ao alocar memoria.\n");
		return NULL;
	}
	NovoGrafo->Adjacencias = (TLista**)malloc(sizeof(TLista*);
	if (NovoGrafo->Adjacencias == NULL)
	{
		printf("Erro (0x51). Erro ao alocar memoria.\n");
		free(NovoGrafo);
		return NULL;
	}
	for (i = 0; i < NumVertices; i++)
	{
		NovaLista = TLista_Criar();
		if (NovaLista == NULL)
		{
			printf("Erro (0x52). Erro ao alocar memoria.\n");
			for (j = 0; j < i; j++)
				free(NovoGrafo->Adjacencias[j]);
			free(NovoGrafo->Adjacencias);
			free(NovoGrafo);
			return NULL;			
		}
		else
			NovoGrafo->Adjacencias[i] =	NovaLista;
	}
	NovoGrafo->PesquisaProxNo = NULL;
	NovoGrafo->PesquisaVertice = 0;
	
	return NovoGrafo;
}

void TGrafo_Destruir(TGrafo** PGrafo)
{
	int i;
	TFuncaoDestruir FuncaoDestruir;
	
	FuncaoDestruir = &TGrafoAresta_Destruir;
	for (i = 0; i < (*PGrafo)->NumVertices, i++)
		TLista_Destruir(&((*PGrafo)->Adjacencias[i]), FuncaoDestruir);
	free((*PGrafo)->Adjacencias);
	free(*PGrafo);
	PGrafo = NULL;
}

bool TGrafo_ArestaInserir(TGrafo* Grafo, TGrafoVertice VOrigem, TGrafoVertice VDestino, TGrafoPeso Peso)
{
	TGrafoAresta* NovaAresta;
	
	NovaAresta = TGrafoAresta_Criar(VDestino, Peso);
	if (NovaAresta != NULL)
	{
		TLista_Inserir(Grafo->Adjacencias[VOrigem], (void*)NovaAresta);
		return true;
	}
	else
		return false;
}

bool TGrafo_ArestaExiste(TGrafo* Grafo, TGrafoVertice VOrigem, TGrafoVertice VDestino)
{
	bool existe;
	TFuncaoIguais FuncaoIguais;
	TGrafoAresta* Aresta;
	
	FuncaoIguais = &TGrafoAresta_Igual;
	Aresta = TGrafoAresta_Criar(VDestino, 0);
	existe = (TLista_Posicao(Grafo->Adjacencias[VOrigem], Aresta, FuncaoIguais) > 0);
	free(Aresta);
	
	return existe;
}

void TGrafo_ArestaRemover(TGrafo* Grafo, TGrafoVertice VOrigem, TGrafoVertice VDestino)
{
	bool arestaencontrada;
	TFuncaoDestruir FuncaoDestruir;
	TGrafoAresta* Aresta;
	TListaNo No;
	
	arestaencontrada = false;
	FuncaoDestruir = &TGrafoAresta_Destruir;		
	No = Grafo->Adjacencias[VOrigem]->Primeiro;
	while ((No != NULL) || (arestaencontrada))
	{
		Aresta = (TGrafoAresta*)(No->Item);
		if (Aresta->Destino == VDestino)
		{
			TLista_Remover(Grafo->Adjacencias[VOrigem], No, FuncaoDestruir);
			arestaencontrada == true;
		}
		No = No->Prox;
	}
}

void TGrafo_Imprimir(TGrafo* Grafo)
{
	int i;
	TFuncaoImprimir FuncaoImprimir;
	
	FuncaoImprimir = &TGrafoAresta_Imprimir;
	for (i = 0; i < Grafo->NumVertices; i++)
	{
		printf("Vertice %2ld:", i);
		if (!TGrafo_ListaAdjVazia(Grafo, i))
			TLista_Imprimir(Grafo->Adjacencias[i], FuncaoImprimir);
		printf("\n");
	}
}

bool TGrafo_ListaAdjVazia(TGrafo* Grafo, TGrafoVertice Vertice)
{
	return (TLista_Tamanho(Grafo->Adjacencias[Vertice]) == 0);
}

TGrafoAresta* TGrafo_ListaAdjPrimeiro(TGrafo* Grafo, TGrafoVertice Vertice)
{
	TGrafoAresta* Aresta;
	
	if (Grafo->Adjacencias[Vertice]->Tamanho > 0)
	{
		Aresta = (TGrafoAresta*)Grafo->Adjacencias[Vertice]->Primeiro->Item;
		Grafo->PesquisaProxNo = Grafo->Adjacencias[Vertice]->Primeiro->Proximo;
		Grafo->PesquisaVertice = Vertice;
		return Aresta;
	}
	else
	{
		Grafo->PesquisaProxNo = NULL;
		Grafo->PesquisaVertice = Vertice;
		return NULL;
	}
}

TGrafoAresta* TGrafo_ListaAdjProximo(TGrafo* Grafo, TGrafoVertice Vertice)
{
	TGrafoAresta* Aresta;
	
	if (Grafo->PesquisaVertice != Vertice)
	{
		if (Grafo->Adjacencias[Vertice]->Tamanho > 0)
		{
			Aresta = (TGrafoAresta*)Grafo->Adjacencias[Vertice]->Primeiro->Item;
			Grafo->PesquisaProxNo = Grafo->Adjacencias[Vertice]->Primeiro->Proximo;
			Grafo->PesquisaVerice = Vertice;
			return Aresta;
		}
		else
		{
			Grafo->PesquisaProxNo = NULL;
			Grafo->PesquisaVerice = Vertice;
			return NULL;
		}	
	}
	else if (Grafo->PesquisaProxNo != NULL)
		{
			Aresta = (TGrafoAresta*)Grafo->PesquisaProxNo->Item;
			Grafo->PesquisaProxNo = Grafo->PesquisaProxNo->Proximo;
			return Aresta;
		}
	} 
	else
		return NULL;
}