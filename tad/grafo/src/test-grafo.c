/*
**	TESTE DO TAD LISTA
**	DOUGLAS RODRIGUES DE ALMEIDA
**
**	Teste do TAD Lista
**	
**/

#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"

int main(void)
{	
	int i;
	int NVertices;
	int NArestas;
	int vertice1, vertice2, peso;
	TGrafo* Grafo;
	TGrafoAresta* Aux;
	
	printf("TESTE GRAFO\n");
	printf("===========\n");
	
	printf("Criando grafo...\n");
	printf("Numero de vertices: ");
	scanf("%d", &NVertices);
	printf("Numero de arestas: ");
	scanf("%d", &NArestas);	
	
	Grafo = TGrafo_Criar(NVertices);
	if (Grafo != NULL)
		printf("OK.\n");
	else
		exit(EXIT_FAILURE);

	printf("Preenchendo arestas...\n");
	for (i = 0; i < NArestas; i++) 
	{
		printf("Nova aresta (%d de %d) (vertice1, vertice2, peso): ", i+1, NArestas);
		scanf("%d, %d, %d", &vertice1, &vertice2, &peso);
		TGrafo_ArestaInserir(Grafo, vertice1, vertice2, peso);
	}
	printf("OK.\n");
	
	printf("Exibindo grafo...\n");
	TGrafo_Imprimir(Grafo);
	printf("OK.\n");
	
	printf("Exibindo lista adjacentes de: ");
	scanf("%d", &vertice1);
	if (!TGrafo_ListaAdjVazia(Grafo, vertice1))
 	{
 		Aux = TGrafo_ListaAdjPrimeiro(Grafo, vertice1);
    	while (Aux) 
		{
			TGrafoAresta_Imprimir((void*)Aux);
			Aux = TGrafo_ListaAdjProximo(Grafo, vertice1);
		}
	}
	printf("OK.\n");

	printf("Removendo aresta...");
	printf("Vertices (vertice1, vertice2):");
	scanf("%d, %d", &vertice1, &vertice2);
	if (TGrafo_ArestaExiste(Grafo, vertice1, vertice2)) 
	{
	    TGrafo_ArestaRemover(Grafo, vertice1, vertice2);
	    printf(" OK.\n");
	}
	else
		printf("Aresta nao existe\n");
		
	printf("Exibindo grafo...\n");
	TGrafo_Imprimir(Grafo);
	printf("OK.\n");		

	printf("Destruindo grafo...");
	TGrafo_Destruir(&Grafo);
	printf("OK.\n");
	
	exit(EXIT_SUCCESS);
}
