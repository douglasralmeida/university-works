/*
**	BIBLIOTECA DO FILIPE
**	DOUGLAS RODRIGUES DE ALMEIDA
**
**	Implementação do sistema da biblioteca
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "strutils.h"
#include "core.h"
#include "livro.h"
#include "ordenador.h"
#include "sistema_consulta.h"
#include "sistema.h"

TSistema* TSistema_Criar(void)
{
	TSistema* NovoSistema;

	NovoSistema = malloc(sizeof(TSistema));
	if (!NovoSistema)
		return NULL;
	NovoSistema->LivrosOrdenados = TArquivo_Criar("livros_ordenados", amlTexto);
	if (!NovoSistema->LivrosOrdenados)
	{
		free(NovoSistema);
		return NULL;
	}
	NovoSistema->Consultas = NULL;

	return NovoSistema;
}

void TSistema_Destruir(TSistema** PSistema)
{
	TFuncaoDestruir FuncaoDestruir;
	
	if ((*PSistema)->LivrosOrdenados)
		TArquivo_Destruir(&(*PSistema)->LivrosOrdenados);
	if ((*PSistema)->Consultas)
	{
		FuncaoDestruir = &TSistemaConsulta_Destruir;
		TFila_Destruir(&(*PSistema)->Consultas, FuncaoDestruir);
	}
	free(*PSistema);
	*PSistema = NULL;
}

void TSistema_LerEntrada(TSistema* Sistema)
{
	char nomelivro[53];
	int tamstring;
	unsigned long numlivros, numestantes, numlivrosporestante, numconsultas;
	unsigned long i;
	TSistemaConsulta* Consulta;
	
	scanf("%lu %lu %lu %lu %lu", &numlivros, &Sistema->MaxItensMemoria, &numestantes, &numlivrosporestante, &numconsultas);
	getchar();
	getchar();

	for (i = 0; i < numlivros; i++)
	{
		fgets(nomelivro, 52, stdin);
		tamstring = strlen(nomelivro);
		TArquivo_ApensarNoFinal(Sistema->LivrosOrdenados, nomelivro, tamstring * sizeof(char));
	}

	Sistema->Consultas = TFila_Criar(numconsultas);
	for (i = 0; i < numconsultas; i++)
	{
		scanf("%50s", nomelivro);
		Consulta = TSistemaConsulta_Criar(nomelivro);
		if (TFila_Enfileirar(Sistema->Consultas, Consulta))
		getchar();		
	}
}

void TSistema_Ordenar(TSistema* Sistema)
{
	TOrdenador* Ordenador;
	TFuncaoComparar TextoComparar;

	TextoComparar = &StrComparar;
	Ordenador = TOrdenador_Criar(Sistema->LivrosOrdenados, TextoComparar, Sistema->MaxItensMemoria);

	TOrdenador_Destruir(&Ordenador);
}

void TSistema_Simular(TSistema* Sistema)
{
	/* 1a. parte -- ordenacao extrena */
	TSistema_Ordenar(Sistema);
	TArquivo_Destruir(&Sistema->LivrosOrdenados);
}
