/*
**	ANDANDO NA FÍSICA
**	DOUGLAS RODRIGUES DE ALMEIDA
**
**	Algo. A*
*/
#include "filaprior.h"
#include "grafo_caminhamento.h"

TVerticeDistancia* TVerticeDistancia_Criar(TGrafoVertice Vertice, size_t Valor)
{
	TVerticeDistancia* NovaDistancia;
	
	NovaDistancia = malloc(sizeof(TVerticeDistancia));
	if (NovaDistancia == NULL)
		return NULL;
	NovaDistancia->Origem = Vertice;
	NovaDistancia->Valor = Valor;
	
	return NovaDistancia;
}

void TVerticeDistancia_Destruir(void** PDistancia)
{
	free(*PDistancia);
	*PDistancia = NULL;	
}

bool TVerticeDistancia_Comparar(void* Distancia1, void* Distancia2)
{
	TVerticeDistancia* Item1;
	TVerticeDistancia* Item2;
	
	Item1 = (TVerticeDistancia*)Distancia1;
	Item2 = (TVerticeDistancia*)Distancia2;

	return (Item1->Valor > Item2->Valor);
}

bool TGrafo_MenorCaminho(TGrafo* Grafo, TGrafoVertice Inicio, TGrafoVertice Final, TFuncaoHeuristica FuncaoHeuristica)
{
	TGrafoVertice verticeadj;
	TGrafoPeso peso;
	size_t* custo;
	size_t novocusto;
	size_t prioridade;
	TFilaPrioridade* fila;
	TVerticeDistancia* item;
	TVerticeDistancia* novoitem;

	custo = malloc(Grafo->NumVertices * sizeof(size_t));
	fila = TFilaPrioridade_Criar(Grafo->NumVertices, &TVerticeDistancia_Comparar);
	custo[Inicio] = 0;
	novoitem = TVerticeDistancia_Criar(Inicio, 0);
	TFilaPrioridade_Enfileirar(fila, novoitem);
	while (TFilaPrioridade_Tamanho(fila) > 0)
	{
		item = TFilaPrioridade_Desenfileirar(fila);
		if (item->Origem == Final)
		{
			Grafo->CustoCaminhamento = custo[item->Origem];
			free(item);
			free(custo);
			TFilaPrioridade_Destruir(&fila, &TVerticeDistancia_Destruir);
			return true;
		}
		if (!TGrafo_ListaAdjVazia(Grafo, item->Origem))
		{
			TGrafo_ListaAdjPrimeiro(Grafo, item->Origem, &verticeadj, &peso);
			novocusto = custo[item->Origem] + peso;
			if ((!custo[verticeadj]) || (novocusto < custo[verticeadj]))
			{
				custo[verticeadj] = novocusto;
				prioridade = novocusto + FuncaoHeuristica(Grafo, verticeadj, Final);
				novoitem = TVerticeDistancia_Criar(verticeadj, prioridade);
				TFilaPrioridade_Enfileirar(fila, novoitem);
			}
			while (TGrafo_ListaAdjProximo(Grafo, item->Origem, &verticeadj, &peso))
			{
				novocusto = custo[item->Origem] + peso;
				if ((!custo[verticeadj]) || (novocusto < custo[verticeadj]))
				{
					custo[verticeadj] = novocusto;
					prioridade = novocusto + FuncaoHeuristica(Grafo, verticeadj, Final);
					novoitem = TVerticeDistancia_Criar(verticeadj, prioridade);
					TFilaPrioridade_Enfileirar(fila, novoitem);
				}
			}
		}
		free(item);
	}
	TFilaPrioridade_Destruir(&fila, &TVerticeDistancia_Destruir);
	free(custo);

	return false;
}
