/*
**	ANDANDO NA FÍSICA
**	DOUGLAS RODRIGUES DE ALMEIDA
**
**	Algo. A*
*/
#include <string.h>
#include "filaprior.h"
#include "mapa_caminhamento.h"

TVerticeDistancia* TVerticeDistancia_Criar(TGrafoVertice Vertice, float Valor)
{
	TVerticeDistancia* NovaDistancia;
	
	NovaDistancia = malloc(sizeof(TVerticeDistancia));
	if (NovaDistancia == NULL)
		return NULL;
	NovaDistancia->Vertice = Vertice;
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

void TMapa_CaminhoPegarChave(TMapa* Mapa, TGrafoVertice Vertice)
{
	int i;
	TMapaInfo* Info;

	Info = TGrafo_ObterVertice(Mapa->Grafo, Vertice);
	if (Info->Tipo == mtChave)
	{
		i = strlen(Mapa->Bolso);
		if (i < Mapa->CapacidadeChaves)
		{
			if (!strchr(Mapa->Bolso, Info->Chave))
			{
				Mapa->Bolso[i] = Info->Chave;
				Mapa->Bolso[i+1] = '\0';
			}
		}
	}
}

float TMapa_CaminhamentoHeuristica(TMapa* Mapa, TGrafoVertice VerticeAtual, TGrafoVertice VerticeDestino)
{
	TMapaInfo* InfoAtual;
	TMapaInfo* InfoDestino;
	float resultado;

	InfoAtual = TGrafo_ObterVertice(Mapa->Grafo, VerticeAtual);
	InfoDestino = TGrafo_ObterVertice(Mapa->Grafo, VerticeDestino);
	resultado = abs(InfoAtual->PosicaoX - InfoDestino->PosicaoX) + abs(InfoAtual->PosicaoY - InfoDestino->PosicaoY);
	resultado *= 1.001;

	return resultado;
}

bool TMapa_CaminhoEstaBloqueado(TMapa* Mapa, TGrafoVertice Vertice)
{
	int i;
	TMapaInfo* Info;
	TMapaChave ChaveNecessaria;

	Info = TGrafo_ObterVertice(Mapa->Grafo, Vertice);
	if (Info->Tipo != mtPorta)
		return false;
	ChaveNecessaria = Info->Chave;
	
	i = 0;
	while (Mapa->Bolso[i] != '\0')
	{
		if (Mapa->Bolso[i] == ChaveNecessaria)
			return false;
		i++;
	}
	return true;
}

bool TMapa_Caminhar(TMapa* Mapa, TGrafoVertice Origem, TGrafoVertice Destino)
{
	TGrafoVertice verticeadj;
	TGrafoPeso peso;
	size_t* custo;
	size_t novocusto;
	float prioridade;
	TFilaPrioridade* fila;
	TVerticeDistancia* item;
	TVerticeDistancia* novoitem;

	custo = calloc(Mapa->Grafo->NumVertices, sizeof(size_t));
	fila = TFilaPrioridade_Criar(Mapa->Grafo->NumVertices, &TVerticeDistancia_Comparar);
	custo[Origem] = 0;
	novoitem = TVerticeDistancia_Criar(Origem, 0);
	TFilaPrioridade_Enfileirar(fila, novoitem);
	while (TFilaPrioridade_Tamanho(fila) > 0)
	{
		item = TFilaPrioridade_Desenfileirar(fila);
		if (item->Vertice == Destino)
		{
			Mapa->CustoCaminhamento += custo[item->Vertice];
			free(item);
			free(custo);
			TFilaPrioridade_Destruir(&fila, &TVerticeDistancia_Destruir);
			return true;
		}
		TMapa_CaminhoPegarChave(Mapa, item->Vertice);
		if (TMapa_CaminhoEBuracoNegro(Mapa->Grafo, item->Vertice, &verticeadj))
		{
			novocusto = custo[item->Vertice];
			custo[item->Vertice] = 0;
			custo[verticeadj] = novocusto;
			prioridade = novocusto + TMapa_CaminhamentoHeuristica(Mapa, verticeadj, Destino);
			novoitem = TVerticeDistancia_Criar(verticeadj, prioridade);
			TFilaPrioridade_Enfileirar(fila, novoitem);
			free(item);
			continue;
		}
		if (TMapa_CaminhoEstaBloqueado(Mapa, item->Vertice))
		{
			free(item);
			continue;
		}		
		if (!TGrafo_ListaAdjVazia(Mapa->Grafo, item->Vertice))
		{				
			TGrafo_ListaAdjPrimeiro(Mapa->Grafo, item->Vertice, &verticeadj, &peso);
			novocusto = custo[item->Vertice] + peso;
			if ((custo[verticeadj] == 0) || (novocusto < custo[verticeadj]))
			{				
				custo[verticeadj] = novocusto;
				prioridade = novocusto + TMapa_CaminhamentoHeuristica(Mapa, verticeadj, Destino);
				novoitem = TVerticeDistancia_Criar(verticeadj, prioridade);
				TFilaPrioridade_Enfileirar(fila, novoitem);
			}
			while (TGrafo_ListaAdjProximo(Mapa->Grafo, item->Vertice, &verticeadj, &peso))
			{
				novocusto = custo[item->Vertice] + peso;
				if ((custo[verticeadj] == 0) || (novocusto < custo[verticeadj]))
				{
					custo[verticeadj] = novocusto;
					prioridade = novocusto + TMapa_CaminhamentoHeuristica(Mapa, verticeadj, Destino);
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
