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
	int vertice1, vertice2, peso);
	TGrafo* Grafo;
	
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
	
	printf("Exibindo grafo...");
	TGrafo_Imprimir(Grafo);
	printf("OK.\n");

	printf("Destruindo grafo...");
	TGrafo_Destruir(&Grafo);
	printf("OK.\n");
	
	exit(EXIT_SUCCESS);
}
