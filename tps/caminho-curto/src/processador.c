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
	int i;
	int ruas, caminhos;
	int rua, caminho, tempo;
	FILE* ArquivoEntrada;
	FILE* ArquivoSaida;
	TFuncaoDestruir FuncaoDestruir;
	
	FuncaoDestruir = &TCaminho_Destruir;
	ArquivoEntrada = fopen(NomeArquivo, "rt");
	ArquivoSaida = fopen("tp2.out", "wt");
	if ((ArquivoEntrada != NULL) && (ArquivoSaida != NULL))
	{
		Processador->Resultado = TLista_Criar(1024);
		fscanf(ArquivoEntrada, "%d %d", &ruas, &caminhos);
		while ((caminhos > 0) && (ruas > 0))
		{
			Processador->Caminhos = TGrafo_Criar(ruas);
			if (Processador->Caminhos != NULL)
			{				
				for (i = 0; i < caminhos; i++)
				{
					fscanf(ArquivoEntrada, "%d %d %d", &rua, &caminho, &tempo);
					TGrafo_ArestaInserir(Processador->Caminhos, rua, caminho, tempo);
				}
				fscanf(ArquivoEntrada, "%d %d", &Processador->Origem, &Processador->Destino);
				TProcessador_MelhorCaminho(Processador);
				fprintf(ArquivoSaida, "%d\n", Processador->MelhorCaminho);
				TGrafo_Destruir(&Processador->Caminhos);
			}
			fscanf(ArquivoEntrada, "%d %d", &ruas, &caminhos);
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

bool TProcessador_MelhorCaminho(TProcessador* Processador)
{
	TFilaPrioridade* Fila;
	TGrafoVertice i;
	Set R;
	
	Fila = TFilaPrioridade_Criar(Procesador->Caminhos->NumVertices);
	Caminho = TCaminho_Criar(Processador->Origem, Processador->Origem, 0);
	TFilaPrioridade_Enfileirar(Fila, (void*)Caminho);
	for (i = 1; i <= Procesador->Caminhos->NumVertices; i++)
	{
		if (i != Procesador->Origem)
		{
			Caminho = TCaminho_Criar(Processador->Origem, i, INFINITY);
			TFilaPrioridade_Enfileirar(Fila, (void*)Caminho);
		}
	}
	while (TFilaPrioridade_Tamanho(Fila) > 0)
	{
		
	}
	
	Processador->MelhorCaminho = -1;

	
	
	if (Processador->MelhorCaminho > -1)
	{
					
	}
	
	TFilaPrioridade_Destruir(&Fila);
	return true;
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
			fprintf(ArquivoSaida, "%d\n", Caminho->TempoMedio);
			No = TLista_Proximo(Processador->Resultado, No);
		}
		Caminho = (TCaminho*)TLista_Item(Processador->Resultado, No);
		fprintf(ArquivoSaida, "%d\n", Caminho->TempoMedio);
	}
	fclose(ArquivoSaida);
}
