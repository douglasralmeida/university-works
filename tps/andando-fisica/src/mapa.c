/*
**	ANDANDO NA FÍSICA
**	DOUGLAS RODRIGUES DE ALMEIDA
**
**	Mapa
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mapa.h"

TMapa* TMapa_Criar(void)
{
	TMapa* NovoMapa;

	NovoMapa = malloc(sizeof(TMapa));
	if (!NovoMapa)
		return NULL;
	NovoMapa->Grafo = NULL;
	NovoMapa->PontoFinal = 0;
	NovoMapa->PontoInicial = 0;	

	return NovoMapa;
}

void TMapa_Destruir(TMapa** PMapa)
{
	if ((*PMapa)->Grafo)
		TGrafo_Destruir(&(*PMapa)->Grafo);
	free(*PMapa);
	*PMapa = NULL;
}

void TMapa_Imprimir(TMapa* Mapa)
{
	printf("MAPA: Vertice Inicio: %lu -- Vertice Fim: %lu\n", Mapa->PontoInicial, Mapa->PontoFinal);
	printf("GRAFO:\n");
	TGrafo_Imprimir(Mapa->Grafo);
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
	int i;
	char* t;
	TGrafoVertice verticedestino, verticeorigem;

	i = 0;
	t = strtok(Linha, " ");
	while (t != NULL)
	{
		verticeorigem = PosicaoX * TamanhoLinha + i;
		if (t[0] >= '0' && t[0] <= '9')
		{		
			Mapa->PodeCaminhar[verticeorigem] = 1;
			verticedestino = (t[0] - '0') * TamanhoLinha + t[1] - '0';
			TGrafo_ArestaInserir(Mapa->Grafo, verticeorigem, verticedestino, 1);			
			if (i > 0)
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
		}
		else
		{			
			switch (t[0])
			{
				case '#':
					Mapa->PodeCaminhar[verticeorigem] = 0;
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
					if (i > 0)
					{
						verticedestino = verticeorigem - 1;
						TMapa_InserirCaminho(Mapa, verticeorigem, verticedestino);
					}
					if (PosicaoX > 0)
					{
						verticedestino = verticeorigem - TamanhoLinha;
						TMapa_InserirCaminho(Mapa, verticeorigem, verticedestino);
					}
				break;
				case 'V':
					Mapa->PodeCaminhar[verticeorigem] = 1;
					Mapa->PontoInicial = PosicaoX * TamanhoLinha + i;
					if (i > 0)
					{
						verticedestino = verticeorigem - 1;
						TMapa_InserirCaminho(Mapa, verticeorigem, verticedestino);
					}
					if (PosicaoX > 0)
					{
						verticedestino = verticeorigem - TamanhoLinha;
						TMapa_InserirCaminho(Mapa, verticeorigem, verticedestino);
					}
				break;
				case 'E':
					Mapa->PodeCaminhar[verticeorigem] = 1;
					Mapa->PontoFinal = PosicaoX * TamanhoLinha + i;
					if (i > 0)
					{
						verticedestino = verticeorigem - 1;
						TMapa_InserirCaminho(Mapa, verticeorigem, verticedestino);
					}
					if (PosicaoX > 0)
					{
						verticedestino = verticeorigem - TamanhoLinha;
						TMapa_InserirCaminho(Mapa, verticeorigem, verticedestino);
					}
				break;
			} 
		}
		i++;
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
	getchar();
	Mapa->Grafo = TGrafo_Criar(altura * largura, true);
	if (!Mapa->Grafo)
		return false;
	Mapa->PodeCaminhar = malloc(altura*largura * sizeof(short));
	for (i = 0; i < altura; i++)
	{
		fgets(linha, 3*largura+1, stdin);
		TMapa_ProcessarLinha(Mapa, linha, i, largura);
	}
	free(Mapa->PodeCaminhar);

	return true;
}
