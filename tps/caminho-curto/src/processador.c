#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "filaprior.h"
#include "grafo.h"
#include "processador.h"

TProcessador* TProcessador_Criar(void)
{
	TProcessador* NovoProcessador;

	NovoProcessador = (TProcessador*)malloc(sizeof(TProcessador));
	if (NovoProcessador == NULL)
	{
		printf("Erro ao alocar memoria.\n");
		return NULL;
	}
	NovoProcessador->Caminhos = NULL;
	NovoProcessador->MelhorCaminho = -1;
	NovoProcessador->Resultado = NULL;
	
	return NovoProcessador;
}

void TProcessador_Destruir(TProcessador** PProcessador)
{
	TFuncaoDestruir FuncaoDestruir;
	
	FuncaoDestruir = &TCaminho_Destruir;
	if ((*PProcessador)->Caminhos != NULL)
		TGrafo_Destruir(&(*PProcessador)->Caminhos);
	if ((*PProcessador)->Resultado != NULL)
		TLista_Destruir(&(*PProcessador)->Resultado, FuncaoDestruir);
	free(*PProcessador);
	PProcessador = NULL;
}

void TProcessador_AnalisarDados(TProcessador* Processador, char* NomeArquivo)
{
	unsigned int i;
	unsigned int ruas, caminhos;
	unsigned int rua, caminho, tempo;
	FILE* ArquivoEntrada;
	FILE* ArquivoSaida;
	TFuncaoDestruir FuncaoDestruir;
	
	FuncaoDestruir = &TCaminho_Destruir;
	ArquivoEntrada = fopen(NomeArquivo, "rt");
	ArquivoSaida = fopen("tp2.out", "wt");
	if ((ArquivoEntrada != NULL) && (ArquivoSaida != NULL))
	{
		Processador->Resultado = TLista_Criar(1024);
		fscanf(ArquivoEntrada, "%u %u", &ruas, &caminhos);
		while ((caminhos > 0) && (ruas > 0))
		{
			Processador->Caminhos = TGrafo_Criar(ruas);
			if (Processador->Caminhos != NULL)
			{				
				for (i = 0; i < caminhos; i++)
				{
					fscanf(ArquivoEntrada, "%u %u %u", &rua, &caminho, &tempo);
					TGrafo_ArestaInserir(Processador->Caminhos, rua, caminho, tempo);
				}
				fscanf(ArquivoEntrada, "%u %u", &Processador->Origem, &Processador->Destino);
				TProcessador_MelhorCaminho(Processador);
				fprintf(ArquivoSaida, "%d\n", Processador->MelhorCaminho);
				TGrafo_Destruir(&Processador->Caminhos);
			}
			fscanf(ArquivoEntrada, "%u %u", &ruas, &caminhos);
		}
		fclose(ArquivoEntrada);
		fclose(ArquivoSaida);
		TProcessador_OrdenarResultado(Processador);
		TProcessador_SalvarVetor(Processador, "xtp2.out");
		TLista_Destruir(&Processador->Resultado, FuncaoDestruir);
	}
	else
		printf("Erro ao abrir arquivo de entrada '%s'.\n", NomeArquivo);
}

void TProcessador_MelhorCaminho(TProcessador* Processador)
{
	TCaminho* Caminho;
	
	Processador->MelhorCaminho = TGrafo_DistanciaMinima(Processador->Caminhos, Processador->Origem, Processador->Destino);
	if (Processador->MelhorCaminho > -1)
	{
		Caminho = TCaminho_Criar(Processador->Origem, Processador->Destino, (unsigned int)Processador->MelhorCaminho);
		TLista_Adicionar(Processador->Resultado, (void*)Caminho);
	}
}

void TProcessador_OrdenarResultado(TProcessador* Processador)
{
	TFuncaoComparar FuncaoComparar;
	
	FuncaoComparar = &TCaminho_Comparar;
	if (TLista_Tamanho(Processador->Resultado) > 1)
		TLista_Ordenar(Processador->Resultado, FuncaoComparar);
}

void TProcessador_SalvarVetor(TProcessador* Processador, char* NomeArquivo)
{
	FILE* ArquivoSaida;
	TCaminho* Caminho;
	TListaNo No;
	
	ArquivoSaida = fopen(NomeArquivo, "wt");
	if (ArquivoSaida == NULL)
	{
		printf("Erro. Erro ao criar arquivo de saida '%s'.\n", NomeArquivo);
		return;
	}
	if (Processador->Resultado->Tamanho > 0)
	{
		No = Processador->Resultado->Primeiro;
		while (No != Processador->Resultado->Ultimo)
		{
			Caminho = (TCaminho*)TLista_Item(Processador->Resultado, No);
			fprintf(ArquivoSaida, "%u\n", Caminho->TempoMedio);
			fprintf(ArquivoSaida, "%u %u\n", Caminho->Origem, Caminho->Destino);
			No = TLista_Proximo(Processador->Resultado, No);
		}
		Caminho = (TCaminho*)TLista_Item(Processador->Resultado, No);
		fprintf(ArquivoSaida, "%u\n", Caminho->TempoMedio);
		fprintf(ArquivoSaida, "%u %u\n", Caminho->Origem, Caminho->Destino);
	}
	fclose(ArquivoSaida);
}
