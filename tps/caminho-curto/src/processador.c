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
	TCaminho* Caminho;
	TFilaPrioridade* Fila;
	TFuncaoComparar FuncaoComparar;
	TGrafoVertice i;
	Set R;
	
	FuncaoComparar = &TGrafoAresta_CompararPeso;
	Fila = TFilaPrioridade_Criar(Procesador->Caminhos->NumVertices, FuncaoComparar);
	Caminho = TCaminho_Criar(Processador->Origem, Processador->Origem, 0);
	TFilaPrioridade_Enfileirar(Fila, (void*)Caminho);
	for (i = 1; i <= Procesador->Caminhos->NumVertices; i++)
	{
		if (i != Procesador->Origem)
		{
			Caminho = TCaminho_Criar(Processador->Origem, i, INFINITO);
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
	
/* pseudocodigo
	void relax(u, v) {
  if (u.dist + w(u,v) < v.dist) {
    v.dist = u.dist + w(u,v);
    v.pred = u;
  }
}

Whenever a vertex's dist value decreases, the min-priority queue must be adjusted accordingly.

Here is pseudocode for Dijkstra's algorithm, assuming that the source vertex is s:
void dijkstra(s) {
  queue = new PriorityQueue<Vertex>();
  for (each vertex v) {
    v.dist = infinity;  // can use Integer.MAX_VALUE or Double.POSITIVE_INFINITY
    queue.enqueue(v);
    v.pred = null;
  }   
  s.dist = 0;

  while (!queue.isEmpty()) {
    u = queue.extractMin();
    for (each vertex v adjacent to u)
      relax(u, v);
  }
}
*/
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
