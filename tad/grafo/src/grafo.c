/*
**	TIPO ABSTRATO DE DADOS GRAFO
**	DOUGLAS RODRIGUES DE ALMEIDA
**
**	Implementacao de grafo com listas de adjacencias usando ponteiros
*/

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "filaprior.h"
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
	NovoGrafo->PesquisaProxNo = NO_NULO;
	
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
	*PGrafo = NULL;
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
	int i;
	TFuncaoDestruir FuncaoDestruir;
	TGrafoAresta* Aresta;
	TListaNo No;
	
	FuncaoDestruir = &TGrafoAresta_Destruir;		
	No = Grafo->Adjacencias[VOrigem-1]->Primeiro;
	for (i = 0; i < TLista_Tamanho(Grafo->Adjacencias[VOrigem-1]); i++)
	{
		Aresta = (TGrafoAresta*)TLista_Item(Grafo->Adjacencias[VOrigem-1], No);
		if (Aresta->Destino == VDestino)
		{
			TLista_Remover(Grafo->Adjacencias[VOrigem-1], No, FuncaoDestruir);
			break;
		}		
		No = TLista_Proximo(Grafo->Adjacencias[VOrigem-1], No);
	}
}

/*-- algoritmo de Dijsktra --*/
int TGrafo_DistanciaMinima(TGrafo* Grafo, TGrafoVertice Origem, TGrafoVertice Destino)
{
	unsigned int i;
	int resultado = -1;
	TFilaPrioridade* Fila;
	TFuncaoComparar FuncaoComparar;
	TGrafoAresta* Aresta;
	TGrafoCaminhoItem* Caminho;
	TGrafoCaminhoItem* CaminhoItemAtual;
	
	/*-- caminho pelo grafo --*/
	Caminho = (TGrafoCaminhoItem*)malloc(Grafo->NumVertices * sizeof(TGrafoCaminhoItem));
	/*-- fila de prioridades para comparar as distancias --*/
	FuncaoComparar = &TGrafoCaminhoItem_Comparar;
	Fila = TFilaPrioridade_Criar(Grafo->NumVertices, FuncaoComparar);
	/*-- todas as distancias da origem ao vertice sao marcadas como infinito
		 exceto o vertice de partida que tem distancia igual a 0 --*/
	for (i = 0; i < Grafo->NumVertices; i++)
	{
		Caminho[i].Antecessor = 0;
		Caminho[i].Vertice = i + 1;
		Caminho[i].Distancia = INT_MAX;
		Caminho[i].JaVisitado = false;
	}
	Caminho[Origem-1].Distancia = 0;
	/*-- adiciona o vertice de origem na fila --*/
	TFilaPrioridade_Enfileirar(Fila, (void*)(Caminho + Origem - 1));
	/*-- le todos os vertices da fila de prioridade --*/
	while (TFilaPrioridade_Tamanho(Fila) > 0)
	{
		/*-- pega o vertice da fila com a menor distancia para a origem no momento --*/
		CaminhoItemAtual = TFilaPrioridade_Desenfileirar(Fila);
		/*-- se cheguei ao destino... --*/
		if (CaminhoItemAtual->Vertice == Destino)
		{
			resultado = Caminho[CaminhoItemAtual->Vertice-1].Distancia;
			break;
		}		
		/*-- hmm...ja passei por aqui entao nao faz nada e pula pro proximo --*/
		if (CaminhoItemAtual->JaVisitado)
			continue;
		/*-- estou passando pela primeira vez, marcar para nao passar de novo --*/
		CaminhoItemAtual->JaVisitado = true;
		/*-- pesquisa a lista de adjacencias do vertice
			 e atualiza a fila de prioridades com as novas 
			 melhores distancias para a origem caso sejam
			 encontradas --*/
		if (!TGrafo_ListaAdjVazia(Grafo, CaminhoItemAtual->Vertice))
		{
			Aresta = TGrafo_ListaAdjPrimeiro(Grafo, CaminhoItemAtual->Vertice);
			while (Aresta) 
			{
				/*-- oba!! achei um caminho melhor! --*/
				if ((!Caminho[Aresta->Destino-1].JaVisitado) && (Caminho[CaminhoItemAtual->Vertice-1].Distancia + (int)Aresta->Peso < Caminho[Aresta->Destino-1].Distancia))
				{
					Caminho[Aresta->Destino-1].Distancia = Caminho[CaminhoItemAtual->Vertice-1].Distancia + Aresta->Peso;
					Caminho[Aresta->Destino-1].Antecessor = CaminhoItemAtual->Vertice;
					/*-- enfileira o vertice encontrado --*/
					TFilaPrioridade_Enfileirar(Fila, (void*)(Caminho + Aresta->Destino - 1));
				}
				Aresta = TGrafo_ListaAdjProximo(Grafo, CaminhoItemAtual->Vertice);
			}
		}
	}
	/*-- limpando a bagunca --*/
	free(Caminho);
	free(Fila->Heap);
	free(Fila);
	
	return resultado;
}

void TGrafo_Imprimir(TGrafo* Grafo)
{
	size_t i;
	TFuncaoImprimir FuncaoImprimir;
	
	FuncaoImprimir = &TGrafoAresta_Imprimir;
	for (i = 1; i <= Grafo->NumVertices; i++)
	{
		printf("Vertice %2d:", (int)i);
		if (!TGrafo_ListaAdjVazia(Grafo, i))
			TLista_Imprimir(Grafo->Adjacencias[i-1], FuncaoImprimir);
		printf("\n");
	}
}

bool TGrafo_ListaAdjVazia(TGrafo* Grafo, TGrafoVertice Vertice)
{
	return (TLista_Tamanho(Grafo->Adjacencias[Vertice-1]) == 0);
}

TGrafoAresta* TGrafo_ListaAdjPrimeiro(TGrafo* Grafo, TGrafoVertice Vertice)
{
	TGrafoAresta* Aresta;
	
	if (TLista_Tamanho(Grafo->Adjacencias[Vertice-1]) > 0)
	{
		Aresta = (TGrafoAresta*)TLista_Item(Grafo->Adjacencias[Vertice-1], Grafo->Adjacencias[Vertice-1]->Primeiro);
		Grafo->PesquisaProxNo = TLista_Proximo(Grafo->Adjacencias[Vertice-1], Grafo->Adjacencias[Vertice-1]->Primeiro);
		return Aresta;
	}
	else
	{
		Grafo->PesquisaProxNo = NO_NULO;
		return NULL;
	}
}

TGrafoAresta* TGrafo_ListaAdjProximo(TGrafo* Grafo, TGrafoVertice Vertice)
{
	TGrafoAresta* Aresta;
	
	if (Grafo->PesquisaProxNo != NO_NULO)
	{
		Aresta = (TGrafoAresta*)TLista_Item(Grafo->Adjacencias[Vertice-1], Grafo->PesquisaProxNo);
		Grafo->PesquisaProxNo = TLista_Proximo(Grafo->Adjacencias[Vertice-1], Grafo->PesquisaProxNo);
		return Aresta;
	} 
	else
		return NULL;
}