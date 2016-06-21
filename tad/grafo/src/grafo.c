/*
**	TIPO ABSTRATO DE DADOS GRAFO
**	DOUGLAS RODRIGUES DE ALMEIDA
**
**	Implementacao de grafo com listas de adjacencias usando ponteiros
*/

#include "list.h"
#include "grafo.h"

TGrafo* TGrafo_Criar(size_t NumVertices)
{
	size_t i;
	size_t j;
	TGrafo* NovoGrafo;
	TLista* NovaLista;
		
	NovoGrafo = (TGrafo*)malloc(sizeof(TGrafo));
	if (NovoGrafo == NULL)
	{
		printf("Erro (0x50). Erro ao alocar memoria.\n");
		return NULL;
	}
	NovoGrafo->Adjacencias = (TLista**)malloc(NumVertices * sizeof(TLista*));
	if (NovoGrafo->Adjacencias == NULL)
	{
		printf("Erro (0x51). Erro ao alocar memoria.\n");
		free(NovoGrafo);
		return NULL;
	}
	for (i = 0; i < NumVertices; i++)
	{
		NovaLista = TLista_Criar(128);
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
	NovoGrafo->NumVertices = NumVertices;
	NovoGrafo->PesquisaProxNo = -1;
	
	return NovoGrafo;
}

void TGrafo_Destruir(TGrafo** PGrafo)
{
	size_t i;
	TFuncaoDestruir FuncaoDestruir;
	
	FuncaoDestruir = &TGrafoAresta_Destruir;
	for (i = 0; i < (*PGrafo)->NumVertices; i++)
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
		TLista_Adicionar(Grafo->Adjacencias[VOrigem-1], (void*)NovaAresta);
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
	
	if (VOrigem > Grafo->NumVertices)
		return false;
	
	FuncaoIguais = &TGrafoAresta_Igual;
	Aresta = TGrafoAresta_Criar(VDestino, 0);
	existe = (TLista_Posicao(Grafo->Adjacencias[VOrigem-1], Aresta, FuncaoIguais) > 0);
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
	No = Grafo->Adjacencias[VOrigem-1]->Primeiro;
	while ((No <= Grafo->Adjacencias[VOrigem-1]->Ultimo) && (!arestaencontrada))
	{
		Aresta = (TGrafoAresta*)TLista_Item(Grafo->Adjacencias[VOrigem-1], No);
		if (Aresta->Destino == VDestino)
		{
			TLista_Remover(Grafo->Adjacencias[VOrigem-1], No, FuncaoDestruir);
			arestaencontrada = true;
		}
		No++;
	}
}

void TGrafo_Imprimir(TGrafo* Grafo)
{
	size_t i;
	TFuncaoImprimir FuncaoImprimir;
	
	FuncaoImprimir = &TGrafoAresta_Imprimir;
	for (i = 0; i < Grafo->NumVertices; i++)
	{
		printf("Vertice %2d:", (int)i+1);
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
	
	if (Grafo->Adjacencias[Vertice-1]->Tamanho > 0)
	{
		Aresta = (TGrafoAresta*)TLista_Item(Grafo->Adjacencias[Vertice-1], Grafo->Adjacencias[Vertice-1]->Primeiro);
		Grafo->PesquisaProxNo = Grafo->Adjacencias[Vertice-1]->Primeiro + 1;
		return Aresta;
	}
	else
	{
		Grafo->PesquisaProxNo = -1;
		return NULL;
	}
}

TGrafoAresta* TGrafo_ListaAdjProximo(TGrafo* Grafo, TGrafoVertice Vertice)
{
	TGrafoAresta* Aresta;
	
	if (Grafo->PesquisaProxNo != -1)
	{
			if (Grafo->PesquisaProxNo < Grafo->Adjacencias[Vertice-1]->Tamanho)
			{
				Aresta = (TGrafoAresta*)TLista_Item(Grafo->Adjacencias[Vertice-1], Grafo->PesquisaProxNo);
				Grafo->PesquisaProxNo++;
			}
			else
				Aresta = NULL;
			return Aresta;
	} 
	else
		return NULL;
}
