/*
**	ANDANDO NA FÍSICA
**	DOUGLAS RODRIGUES DE ALMEIDA
**
**	Mapa
*/
#include <stdio.h>
#include <stdlib.h>

void TMapa_ProcessarLinha(TMapa* Mapa, char* String, int Linha, int Tamanho)
{
	int i;
	char s[3];
	size_t posicao;
	TMapaItem* Item;

	for (i = 0; i < Tamanho; i++)
	{
		sscanf(String, "%s", s);
		Item = malloc(sizeof(TMapaItem));
		Item->DestinoH = 0;
		Item->DestinoV = 0;
		Item->ID = s[0];
		if (s[0] >= '0' && s[0] <= '9')
		{
			Item->ID = 'B';
			Item->DestinoH = s[0];
			Item->DestinoV = s[1];
		} else
		{
			switch (s[0])
			{
				case 'V':
					Mapa->PontoInicio[0] = Linha;
					Mapa->PontoInicio[1] = i;
				break;

				case 'E':
					Mapa->PontoFim[0] = Linha;
					Mapa->PontoFim[1] = i;
				break;
			}
		}
		posicao = Linha * Mapa->Grafo->NumVertices + i;
		TGrafo_VerticeGravarDados(Mapa->Grafo, posicao);
	}
}

bool TMapa_ProcessarEntrada(TMapa* Mapa)
{
	int i;
	int altura, largura, capacidade_chaves;
	char linha[20];

	fscanf("%d %d %d", &altura, &largura, &capacidade_chaves);
	for (i = 0; i < altura; i++)
	{
		fscanf("%s", linha);
		TMapa_ProcessarLinha(Mapa, linha, i, 9);
	}
}

void TMapa_ProcessarGrafo(TMapa* Mapa)
{
	
}
