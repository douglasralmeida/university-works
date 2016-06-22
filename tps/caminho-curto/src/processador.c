#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "grafo.h"
#include "processador.h"

TProcessador* TTProcessador_Criar(void)
{
	TProcessador* NovoProcessador;

	NovoProcessador = (TProcessador*)malloc(sizeof(TProcessador));
	if (NovoProcessador == NULL)
	{
		printf("Erro ao alocar memoria.\n");
		return NULL;
	}
	Processador->Caminhos = NULL:
	
	return NovoProcessador;
}

void TProcessador_Destruir(TProcessador** PProcessador)
{
	if ((*PProcessador)->Grafos != NULL)
		TGrafo_Destruir(&(*PProcessador)->Caminhos);
	free(*PProcessador);
	PProcessador = NULL;
}

void TProcessador_AnalisarDados(TProcessador* Processador);
{
	TProcessador_MelhorCaminho(Processador);
	/*-- salvar o vetor de resultados (somente o peso) --*/
	TProcessador_OrdenarResultado(Processador);
	/*-- salvar o vetor de resultados ordenado(tad completo) --*/
}

bool TProcessador_CarregarDados(TProcessador* Processador, char* NomeArquivo)
{
	int i;
	int ruas, caminhos;
	int rua, caminho, tempo;
	int origiem, destino;
	FILE* ArquivoEntrada;
	
	ArquivoEntrada = fopen(NomeArquivo, "rt");
	if (ArquivoEntrada != NULL)
	{
		fscanf(ArquivoEntrada, "%d %d", &ruas, &caminhos);
		while ((caminhos > 0) && (ruas > 0))
		{
			Processador->Caminhos = TGrafo_Criar(ruas);
			if (Processador->Caminhos != NULL)
			{				
				for (i = 0; i < caminhos; i++)
				{
					fscanf(ArquivoEntrada, "%d %d %d", &rua, &caminho, &tempo);
					TGrafo_ArestaAdicionar(Processador->Caminhos, rua, caminho, tempo);
				}
				fscanf("%d %d", &origem, &destino);
				
				/*-- chamar algo. melhor caminho --*/
				/*-- chamar algo. salvar resultado --*/
								
				TGrafo_Destruir(&Processador->Caminhos);
			}
		}		
		fclose(ArquivoEntrada);
	}
	else
	{
		printf("Erro ao abrir arquivo de entrada '%s'.\n", NomeArquivo);
	}
	
	return (ArquivoEntrada != NULL);
}

bool TProcessador_MelhorCaminho(TProcessador* Processador)
{
	/*-- encontrar o melhor caminho --*/
}

void TProcessador_OrdenarResultado(TProcessador* Processador)
{
	/*-- ordenar vetor de resultados --*/
}

bool TProcessador_SalvarResultado(TProcessador* Processador, char* NomeArquivo)
{
	FILE* ArquivoSaida;
	
	ArquivoSaida = fopen(NomeArquivo, "wt");
	if (ArquivoSaida == NULL)
	{
		printf("Erro. Erro ao criar arquivo de saida '%s'.\n", NomeArquivo);
		return false;
	}
	/*-- salvar os dados aqui --*/
	fclose(ArquivoSaida);
	
	return true;
}
