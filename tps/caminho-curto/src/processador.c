#include <stdio.h>
#include <stdlib.h>
#include "list.h"
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
	Processador->MelhorCaminho = -1;
	return true;
}

void TProcessador_OrdenarResultado(TProcessador* Processador)
{
	if (TLista_Tamanho(Processador->Resultado) > 0)
		Processador->Resultado->Tamanho = 0;
}

void TProcessador_SalvarVetor(TProcessador* Processador, char* NomeArquivo)
{
	FILE* ArquivoSaida;
	
	ArquivoSaida = fopen(NomeArquivo, "wt");
	if (ArquivoSaida == NULL)
	{
		printf("Erro. Erro ao criar arquivo de saida '%s'.\n", NomeArquivo);
		return;
	}
	Processador->Resultado->Tamanho = 0;
	fclose(ArquivoSaida);
}
