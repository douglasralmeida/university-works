/*
**	ANDANDO NA FÍSICA
**	DOUGLAS RODRIGUES DE ALMEIDA
**
**	Mapa
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "grafo_caminhamento.h"
#include "mapa.h"

TMapaInfo* TMapaInfo_Criar(TMapaPos PosicaoX, TMapaPos PosicaoY)
{
	TMapaInfo* NovaInfo;

	NovaInfo = malloc(sizeof(TMapaInfo));
	if (!NovaInfo)
		return NULL;
	NovaInfo->PosicaoX = PosicaoX;
	NovaInfo->PosicaoY = PosicaoY;

	return NovaInfo;
}

void TMapaInfo_Destruir(void** PInfo)
{
	free(*PInfo);
	*PInfo = NULL;
}

TMapa* TMapa_Criar(void)
{
	TMapa* NovoMapa;

	NovoMapa = malloc(sizeof(TMapa));
	if (!NovoMapa)
		return NULL;
	NovoMapa->Grafo = NULL;
	NovoMapa->PontoFinal = 0;
	NovoMapa->PontoInicial = 0;
	NovoMapa->TemSaida = false;
	NovoMapa->TempoMinimo = -1;

	return NovoMapa;
}

void TMapa_Destruir(TMapa** PMapa)
{
	if ((*PMapa)->Grafo)
		TGrafo_Destruir(&(*PMapa)->Grafo);
	free(*PMapa);
	*PMapa = NULL;
}

TGrafoPeso TMapa_CaminhamentoHeuristica(TGrafo* Grafo, TGrafoVertice VerticeAtual, TGrafoVertice VerticeDestino)
{
	TMapaInfo* InfoAtual;
	TMapaInfo* InfoDestino;

	InfoAtual = TGrafo_ObterVertice(Grafo, VerticeAtual);
	InfoDestino = TGrafo_ObterVertice(Grafo, VerticeDestino);
	
	return abs(InfoAtual->PosicaoX - InfoDestino->PosicaoX) + abs(InfoAtual->PosicaoY - InfoDestino->PosicaoY);
}

void TMapa_EncontrarMenorCaminho(TMapa* Mapa)
{
	Mapa->TemSaida = TGrafo_MenorCaminho(Mapa->Grafo, Mapa->PontoInicial, Mapa->PontoFinal, &TMapa_CaminhamentoHeuristica);
}

void TMapa_ImprimirResultado(TMapa* Mapa)
{
	if (Mapa->TemSaida)
		printf("%lu", Mapa->Grafo->CustoCaminhamento);
	else
		printf("-1");
}

void TMapa_InserirCaminho(TMapa* Mapa, TGrafoVertice Origem, TGrafoVertice Destino)
{
	if (Mapa->PodeCaminhar[Destino])
	{
		TGrafo_ArestaInserir(Mapa->Grafo, Origem, Destino, 1);
		TGrafo_ArestaInserir(Mapa->Grafo, Destino, Origem, 1);
	}
}

void TMapa_ProcessarLinha(TMapa* Mapa, char* Linha, int PosicaoX, int TamanhoLinha)
{
	int PosicaoY;
	char* t;
	TGrafoVertice verticedestino, verticeorigem;
	TMapaInfo* Info;

	PosicaoY = 0;
	t = strtok(Linha, " ");
	while (t != NULL)
	{
		verticeorigem = PosicaoX * TamanhoLinha + PosicaoY;
		if (t[0] >= '0' && t[0] <= '9')
		{		
			Mapa->PodeCaminhar[verticeorigem] = 1;
			verticedestino = (t[0] - '0') * TamanhoLinha + t[1] - '0';
			TGrafo_ArestaInserir(Mapa->Grafo, verticeorigem, verticedestino, 1);
			if (PosicaoY > 0)
			{
				verticedestino = verticeorigem - 1;
				if (Mapa->PodeCaminhar[verticedestino])
					TGrafo_ArestaInserir(Mapa->Grafo, verticedestino, verticeorigem, 1);
			}
			if (PosicaoX > 0)
			{
				verticedestino = verticeorigem - TamanhoLinha;
				if (Mapa->PodeCaminhar[verticedestino])
					TGrafo_ArestaInserir(Mapa->Grafo, verticedestino, verticeorigem, 1);
			}	
			Info = TMapaInfo_Criar(PosicaoX, PosicaoY);
			Info->Tipo = mtBuracoNegro;
			Info->Chave = '\0';
			TGrafo_DefinirVertice(Mapa->Grafo, verticeorigem, Info);
		}
		else
		{			
			switch (t[0])
			{
				case '#':
					Mapa->PodeCaminhar[verticeorigem] = 0;
					Info = TMapaInfo_Criar(PosicaoX, PosicaoY);
					Info->Tipo = mtParede;
					Info->Chave = '\0';
					TGrafo_DefinirVertice(Mapa->Grafo, verticeorigem, Info);
				break;
				case 'c':
				case 'd':
				case 'h':
				case 's':
				case 'C':
				case 'D':
				case 'H':
				case 'S':
				case '.':
					Mapa->PodeCaminhar[verticeorigem] = 1;
					if (PosicaoY > 0)
					{
						verticedestino = verticeorigem - 1;
						TMapa_InserirCaminho(Mapa, verticeorigem, verticedestino);
					}
					if (PosicaoX > 0)
					{
						verticedestino = verticeorigem - TamanhoLinha;
						TMapa_InserirCaminho(Mapa, verticeorigem, verticedestino);
					}
					Info = TMapaInfo_Criar(PosicaoX, PosicaoY);
					Info->Tipo = mtCaminhavel;
					Info->Chave = '\0';
					TGrafo_DefinirVertice(Mapa->Grafo, verticeorigem, Info);
				break;
				case 'V':
					Mapa->PodeCaminhar[verticeorigem] = 1;
					Mapa->PontoInicial = verticeorigem;
					if (PosicaoY > 0)
					{
						verticedestino = verticeorigem - 1;
						TMapa_InserirCaminho(Mapa, verticeorigem, verticedestino);
					}
					if (PosicaoX > 0)
					{
						verticedestino = verticeorigem - TamanhoLinha;
						TMapa_InserirCaminho(Mapa, verticeorigem, verticedestino);
					}
					Info = TMapaInfo_Criar(PosicaoX, PosicaoY);
					Info->Tipo = mtInicio;
					Info->Chave = '\0';
					TGrafo_DefinirVertice(Mapa->Grafo, verticeorigem, Info);
				break;
				case 'E':
					Mapa->PodeCaminhar[verticeorigem] = 1;
					Mapa->PontoFinal = verticeorigem;
					if (PosicaoY > 0)
					{
						verticedestino = verticeorigem - 1;
						TMapa_InserirCaminho(Mapa, verticeorigem, verticedestino);
					}
					if (PosicaoX > 0)
					{
						verticedestino = verticeorigem - TamanhoLinha;
						TMapa_InserirCaminho(Mapa, verticeorigem, verticedestino);
					}
					Info = TMapaInfo_Criar(PosicaoX, PosicaoY);
					Info->Tipo = mtFim;
					Info->Chave = '\0';
					TGrafo_DefinirVertice(Mapa->Grafo, verticeorigem, Info);
				break;
			}
		}
		PosicaoY++;
		t = strtok(NULL, " ");
	}
}

bool TMapa_ProcessarEntrada(TMapa* Mapa)
{
	size_t i;
	size_t altura, largura, capacidade_chaves;
	char linha[20];

	scanf("%lu %lu %lu", &altura, &largura, &capacidade_chaves);
	getchar();
	Mapa->Grafo = TGrafo_Criar(altura*largura, true);
	if (!Mapa->Grafo)
		return false;
	Mapa->PodeCaminhar = malloc(altura*largura * sizeof(short));
	if (!Mapa->PodeCaminhar)
	{
		free(Mapa->Grafo);
		return false;
	}
	for (i = 0; i < altura; i++)
	{
		fgets(linha, 3*largura+1, stdin);
		TMapa_ProcessarLinha(Mapa, linha, i, largura);
	}
	free(Mapa->PodeCaminhar);

	return true;
}
