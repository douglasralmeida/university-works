/*
**	BIBLIOTECA DO FILIPE
**	DOUGLAS RODRIGUES DE ALMEIDA
**
**	Implementação do sistema da biblioteca
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
	NovoSistema->Consultas = NULL;
	NovoSistema->MaxItensMemoria = 0;
	NovoSistema->QuantLivros = 0;

	return NovoSistema;
}

void TSistema_Destruir(TSistema** PSistema)
{
	TFuncaoDestruir FuncaoDestruir;
	
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
	char nomelivro[51];
	unsigned long numestantes, numlivrosporestante, numconsultas;
	unsigned long i;
	TLivro* Livro;
	TSistemaConsulta* Consulta;
	TArquivo* ArquivoTemp;

	scanf("%lu %lu %lu %lu %lu", &Sistema->QuantLivros, &Sistema->MaxItensMemoria, &numestantes, &numlivrosporestante, &numconsultas);
	getchar();
	ArquivoTemp = TArquivo_Criar("temp", amlBinario);
	if (!ArquivoTemp)
	{
		perror("Erro: Arquivo temporario nao pôde ser criado.\n");
		return;
	}
	Livro = TLivro_Criar();
	if (!Livro)
	{
		perror("Erro: Estrutura TLivro nao pôde ser criada.\n");
		TArquivo_Destruir(&ArquivoTemp);
		return;
	}
	for (i = 0; i < Sistema->QuantLivros; i++)
	{
		scanf("%50s %c", Livro->Titulo, &Livro->Disponivel);
		TArquivo_ApensarAgora(ArquivoTemp, Livro, sizeof(TLivro));
		memset(Livro->Titulo, '\0', 50);
	}
	TArquivo_Destruir(&ArquivoTemp);
	TLivro_Destruir(&Livro);
	Sistema->Consultas = TFila_Criar(numconsultas);
	if (!Sistema->Consultas)
		return;
	for (i = 0; i < numconsultas; i++)
	{
		scanf("%50s", nomelivro);
		Consulta = TSistemaConsulta_Criar(nomelivro);
		if (TFila_Enfileirar(Sistema->Consultas, Consulta))
		getchar();		
	}
}

void TSistema_OrdenarLivros(TSistema* Sistema)
{
	int i;
	TLivro* Livro;
	TOrdenador* Ordenador;
	TFuncaoComparar FuncaoComparar;
	TFuncaoCopiar FuncaoCopiar;

	FuncaoComparar = &TLivro_Comparar;
	FuncaoCopiar = &TLivro_Copiar;
	Ordenador = TOrdenador_Criar("temp", FuncaoComparar, FuncaoCopiar, Sistema->MaxItensMemoria);
	Livro = TLivro_Criar();
	Livro->Titulo[0] = '_';
	Livro->Titulo[1] = '\0';
	Ordenador->LimiteInferior = Livro;
	Livro = TLivro_Criar();
	for (i = 0; i < 50; i++)
		Livro->Titulo[i] = 'z';
	Livro->Titulo[50] = '\0';
	Ordenador->LimiteSuperior = Livro;
	Ordenador->TamRegistro = sizeof(TLivro);
	Ordenador->Quantidade = Sistema->QuantLivros;
	TOrdenador_Ordenar(Ordenador);
	printf("%s\n", ((TLivro*)Ordenador->LimiteInferior)->Titulo);
	TLivro_Destruir((TLivro**)&Ordenador->LimiteInferior);
	TLivro_Destruir((TLivro**)&Ordenador->LimiteSuperior);
	TOrdenador_Destruir(&Ordenador);
}

void TSistema_SalvarLivros(TSistema* Sistema, char* NomeArquivo)
{
	TArquivo* ArquivoLivros;
	TLivro* Livro;
	FILE* ArquivoTemp;
	char String[54];
	unsigned long i; 
	int tamtitulo;

	Livro = TLivro_Criar();
	ArquivoTemp = fopen("temp", "rb");
	ArquivoLivros = TArquivo_Criar(NomeArquivo, amlTexto);
	for (i = 0; i < Sistema->QuantLivros; i++)
	{
		fread(Livro, sizeof(TLivro), 1, ArquivoTemp);
		strcpy(String, Livro->Titulo);
		tamtitulo = strlen(String);
		String[tamtitulo] = ' ';
		String[tamtitulo+1] = Livro->Disponivel;
		String[tamtitulo+2] = '\n';
		String[tamtitulo+3] = '\0';
		TArquivo_ApensarAgora(ArquivoLivros, String, (tamtitulo + 3) * sizeof(char));
	}
	fclose(ArquivoTemp);
	TArquivo_Destruir(&ArquivoLivros);
	TLivro_Destruir(&Livro);
}

void TSistema_Simular(TSistema* Sistema)
{
	/* 1a. parte -- ordenacao extrena */
	TSistema_OrdenarLivros(Sistema);
	TSistema_SalvarLivros(Sistema, "livros_ordenados");  
}
