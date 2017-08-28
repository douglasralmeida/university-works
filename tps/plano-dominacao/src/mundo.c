/*
**	PLANO DE DOMINAÇÃO
**	DOUGLAS RODRIGUES DE ALMEIDA
**
**	Implementação do TAD Mundo
*/
#include <stdio.h>
#include <stdlib.h>
#include "mundo.h"

TMundo* TMundo_Criar(unsigned long long Altura, unsigned long long Largura)
{
	TMundo* NovoMundo;

	NovoMundo = malloc(sizeof(TMundo));
	if (!NovoMundo)
		return NULL;
	NovoMundo->Cidades = malloc(Altura * Largura * sizeof(TPopulacao));
	NovoMundo->Altura = Altura;
	NovoMundo->Largura = Largura;
	NovoMundo->PopulacaoTotal = 0;
	if (!NovoMundo->Cidades)
	{
		free(NovoMundo);
		return NULL;
	}

	return NovoMundo;
}

void TMundo_Destruir(TMundo** PMundo)
{
	free((*PMundo)->Cidades);
	free(*PMundo);
	*PMundo = NULL;
}

void TMundo_ExibirMatriz(TMundo* Mundo)
{
	total = Mundo->Altura * Mundo->Largura;
	while (contador < total)
	{
		scanf("%llu", Mundo->Cidades + contador);
		contador++;
	}	
}

void TMundo_ExibirResultado(TMundo* Mundo)
{
	printf("%llu", Mundo->PopulacaoTotal);
}

void TMundo_Processar(TMundo* Mundo)
{
	Mundo->PopulacaoTotal = 0;
}

void TMundo_ReceberEntrada(TMundo* Mundo)
{
	unsigned long long total;
	unsigned long long contador=0;

	total = Mundo->Altura * Mundo->Largura;
	while (contador < total)
	{
		scanf("%llu", Mundo->Cidades + contador);
		contador++;
	}	
}
