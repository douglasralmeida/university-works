/*
**	ANDANDO NA FÍSICA
**	DOUGLAS RODRIGUES DE ALMEIDA
**
**	Algo. A*
*/
#include "filaprior.h"
#include "mapa_caminhamento.h"

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

bool TMapa_CaminhoEBuracoNegro(TGrafo* Grafo, TGrafoVertice Vertice, TGrafoVertice* Destino)
{
	bool passou;
	TMapaInfo* Info;

	Info = TGrafo_ObterVertice(Grafo, Vertice);
	*Destino = Info->DestinoBuraco;
	passou = !Info->Passou;
	Info->Passou = 1;

	return (Info->Tipo == mtBuracoNegro && passou);
}

TGrafoPeso TMapa_CaminhamentoHeuristica(TMapa* Mapa, TGrafoVertice VerticeAtual, TGrafoVertice VerticeDestino)
{
	TMapaInfo* InfoAtual;
	TMapaInfo* InfoDestino;

	InfoAtual = TGrafo_ObterVertice(Mapa->Grafo, VerticeAtual);
	InfoDestino = TGrafo_ObterVertice(Mapa->Grafo, VerticeDestino);
	
	return abs(InfoAtual->PosicaoX - InfoDestino->PosicaoX) + abs(InfoAtual->PosicaoY - InfoDestino->PosicaoY);
}

bool TMapa_MenorCaminho(TMapa* Mapa)
{
	TGrafoVertice verticeadj;
	TGrafoPeso peso;
	size_t* custo;
	size_t novocusto;
	size_t prioridade;
	TFilaPrioridade* fila;
	TVerticeDistancia* item;
	TVerticeDistancia* novoitem;

	custo = malloc(Mapa->Grafo->NumVertices * sizeof(size_t));
	fila = TFilaPrioridade_Criar(Mapa->Grafo->NumVertices, &TVerticeDistancia_Comparar);
	custo[Mapa->PontoInicial] = 0;
	novoitem = TVerticeDistancia_Criar(Mapa->PontoInicial, 0);
	TFilaPrioridade_Enfileirar(fila, novoitem);
	while (TFilaPrioridade_Tamanho(fila) > 0)
	{
		item = TFilaPrioridade_Desenfileirar(fila);
		if (item->Origem == Mapa->PontoFinal)
		{
			Mapa->CustoCaminhamento = custo[item->Origem];
			free(item);
			free(custo);
			TFilaPrioridade_Destruir(&fila, &TVerticeDistancia_Destruir);
			return true;
		}
		if (TMapa_CaminhoEBuracoNegro(Mapa->Grafo, item->Origem, &verticeadj))
		{
			novocusto = custo[item->Origem] + 1;
			custo[verticeadj] = novocusto;
			prioridade = novocusto + TMapa_CaminhamentoHeuristica(Mapa, verticeadj, Mapa->PontoFinal);
			novoitem = TVerticeDistancia_Criar(verticeadj, prioridade);
			TFilaPrioridade_Enfileirar(fila, novoitem);
		}
		if (!TGrafo_ListaAdjVazia(Mapa->Grafo, item->Origem))
		{			
			TGrafo_ListaAdjPrimeiro(Mapa->Grafo, item->Origem, &verticeadj, &peso);
			novocusto = custo[item->Origem] + peso;
			if ((!custo[verticeadj]) || (novocusto < custo[verticeadj]))
			{
				custo[verticeadj] = novocusto;
				prioridade = novocusto + TMapa_CaminhamentoHeuristica(Mapa, verticeadj, Mapa->PontoFinal);
				novoitem = TVerticeDistancia_Criar(verticeadj, prioridade);
				TFilaPrioridade_Enfileirar(fila, novoitem);
			}
			while (TGrafo_ListaAdjProximo(Mapa->Grafo, item->Origem, &verticeadj, &peso))
			{
				novocusto = custo[item->Origem] + peso;
				if ((!custo[verticeadj]) || (novocusto < custo[verticeadj]))
				{
					custo[verticeadj] = novocusto;
					prioridade = novocusto + TMapa_CaminhamentoHeuristica(Mapa, verticeadj, Mapa->PontoFinal);
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
