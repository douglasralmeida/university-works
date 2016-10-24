/*
**	ANDANDO NA FÍSICA
**	DOUGLAS RODRIGUES DE ALMEIDA
**
**	Mapa
*/
#include <stdio.h>
#include <stdlib.h>

void TMapa_ProcessarLinha(char* Linha, int Numero, int Tamanho)
{
	int i;

	for (i = 0; i < Tamanho; i++)
	{
		TGrafo_AdicionarAresta(Mapa->Grafo, Numero + i, Numero + i + 1);
	}
}

bool TMapa_ProcessarEntrada(void)
{
	int i;
	int altura, largura, capacidade_chaves;
	char linha[10];

	fscanf("%d %d %d", &altura, &largura, &capacidade_chaves);
	for (i = 0; i < altura; i++)
	{
		fscanf("%s", linha);
		TMapa_ProcessarLinha(linha, i, 9);
	}
}
