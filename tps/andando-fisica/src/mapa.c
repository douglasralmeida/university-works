/*
**	ANDANDO NA FÍSICA
**	DOUGLAS RODRIGUES DE ALMEIDA
**
**	Mapa
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "filaprior.h"
#include "mapa.h"
#include "mapa_caminhamento.h"

TMapaCaminho* TMapaCaminho_Criar(TMapaChave Chave, TGrafoVertice Vertice)
{
	TMapaCaminho* NovoCaminho;

	NovoCaminho = malloc(sizeof(TMapaCaminho));
	NovoCaminho->Chave = Chave;
	NovoCaminho->LocalChave = Vertice;

	return NovoCaminho;
}

void TMapaCaminho_Destruir(void** PCaminho)
{
	free(*PCaminho);
	*PCaminho = NULL;
}

TMapaInfo* TMapaInfo_Criar(TMapaPos PosicaoX, TMapaPos PosicaoY)
{
	TMapaInfo* NovaInfo;

	NovaInfo = malloc(sizeof(TMapaInfo));
	if (!NovaInfo)
		return NULL;
	NovaInfo->PosicaoX = PosicaoX;
	NovaInfo->PosicaoY = PosicaoY;
	NovaInfo->Passou = 0;
	NovaInfo->DestinoBuraco = 0;

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
	NovoMapa->CapacidadeChaves = 0;
	NovoMapa->Chaves = TLista_Criar(4);
	NovoMapa->PontoFinal = 0;
	NovoMapa->PontoInicial = 0;
	NovoMapa->TemSaida = false;
	NovoMapa->CustoCaminhamento = 0;
	NovoMapa->CustoFinal = 0;

	return NovoMapa;
}

void TMapa_Destruir(TMapa** PMapa)
{
	if ((*PMapa)->Grafo)
		TGrafo_Destruir(&(*PMapa)->Grafo);
	if ((*PMapa)->Chaves)
		TLista_Destruir(&(*PMapa)->Chaves, &TMapaCaminho_Destruir);
	free(*PMapa);
	*PMapa = NULL;
}

void TMapa_EncontrarMenorCaminho(TMapa* Mapa)
{
	int i;
	bool achousaida;
	TMapaCaminho* Caminho;

	Mapa->Bolso = malloc((Mapa->CapacidadeChaves + 1) * sizeof(char));
	Mapa->Bolso[0] = '\0';
	Mapa->CustoCaminhamento = 0;
	Mapa->TemSaida = TMapa_Caminhar(Mapa, Mapa->PontoInicial, Mapa->PontoFinal);
	if (Mapa->TemSaida)
		Mapa->CustoFinal = Mapa->CustoCaminhamento;
	for (i = 0; i < TLista_Tamanho(Mapa->Chaves); i++)
	{
		Caminho = TLista_Item(Mapa->Chaves, i);
		Mapa->CustoCaminhamento = 0;
		achousaida = TMapa_Caminhar(Mapa, Mapa->PontoInicial, Caminho->LocalChave);
		if (achousaida)
		{
			achousaida = TMapa_Caminhar(Mapa, Caminho->LocalChave, Mapa->PontoFinal);
			if (achousaida)
			{
				if (Mapa->CustoCaminhamento < Mapa->CustoFinal || Mapa->CustoFinal == 0)
				{
					Mapa->CustoFinal = Mapa->CustoCaminhamento;
					Mapa->TemSaida = true;
				}
			}
		}
	}
	free(Mapa->Bolso);
}

void TMapa_ImprimirResultado(TMapa* Mapa)
{
	if (Mapa->TemSaida)
		printf("%lu", Mapa->CustoFinal);
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

void TMapa_ProcessarLinha(TMapa* Mapa, char* Linha, int PosicaoX, int TamanhoLinha, int Altura)
{
	int PosicaoY;
	char* t;
	TGrafoVertice verticedestino, verticeorigem;
	TMapaCaminho* Caminho;
	TMapaInfo* Info;
	int i;

	PosicaoY = 0;
	t = strtok(Linha, " ");
	while (t != NULL)
	{
		Info = TMapaInfo_Criar(PosicaoX, PosicaoY);
		verticeorigem = PosicaoX * TamanhoLinha + PosicaoY;
		if (t[0] >= '0' && t[0] <= '9')
		{
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
			Info->Tipo = mtBuracoNegro;
			Info->Chave = '\0';
			i = (Altura - 1 - t[0] + '0') *  TamanhoLinha + t[1] - '0';
			verticedestino = (TGrafoVertice)i;
			Info->DestinoBuraco = verticedestino;
		}
		else
		{			
			switch (t[0])
			{
				case '#':
					Mapa->PodeCaminhar[verticeorigem] = 0;
					Info->Tipo = mtParede;
					Info->Chave = '\0';
				break;
				case 'c':
				case 'd':
				case 'h':
				case 's':
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
					Info->Tipo = mtChave;
					Info->Chave = t[0];
					Caminho = TMapaCaminho_Criar(Info->Chave, verticeorigem);
					TLista_Adicionar(Mapa->Chaves, Caminho);
				break;
				case 'C':
				case 'D':
				case 'H':
				case 'S':
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
					Info->Tipo = mtPorta;
					Info->Chave = t[0] + 32;
				break;
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
					Info->Tipo = mtCaminhavel;
					Info->Chave = '\0';
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
					Info->Tipo = mtInicio;
					Info->Chave = '\0';
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
					Info->Tipo = mtFim;
					Info->Chave = '\0';
				break;
			}
		}
		TGrafo_DefinirVertice(Mapa->Grafo, verticeorigem, Info);
		PosicaoY++;
		t = strtok(NULL, " ");
	}
}

bool TMapa_ProcessarEntrada(TMapa* Mapa)
{
	size_t i;
	size_t altura, largura;
	char linha[20];

	scanf("%lu %lu %hu", &altura, &largura, &Mapa->CapacidadeChaves);
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
		TMapa_ProcessarLinha(Mapa, linha, i, largura, altura);
	}
	free(Mapa->PodeCaminhar);

	return true;
}
