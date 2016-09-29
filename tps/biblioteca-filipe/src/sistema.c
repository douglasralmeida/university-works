/*
**	BIBLIOTECA DO FILIPE
**	DOUGLAS RODRIGUES DE ALMEIDA
**
**	Implementação do sistema da biblioteca
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "livro.h"
#include "ordenador.h"
#include "sistema_consulta.h"
#include "sistema_es.h"
#include "sistema.h"

TSistema* TSistema_Criar(void)
{
	TSistema* NovoSistema;

	NovoSistema = malloc(sizeof(TSistema));
	if (!NovoSistema)
		return NULL;
	NovoSistema->Consultas = NULL;
	NovoSistema->MaxItensMemoria = 0;
	NovoSistema->NomeEstante = "estante";
	NovoSistema->NomeIndice = "indice";
	NovoSistema->NomeLivrosOrdenados = "livros_ordenados";
	NovoSistema->NomeTemp = "temp";
	NovoSistema->QuantEstantes = 0;
	NovoSistema->QuantLivros = 0;
	NovoSistema->QuantLivrosEstantes = 0;

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

bool TSistema_OrdenarLivros(TSistema* Sistema)
{
	int i;
	TLivro* Livro;
	TOrdenador* Ordenador;
	TFuncaoComparar FuncaoComparar;
	TFuncaoCopiar FuncaoCopiar;

	FuncaoComparar = &TLivro_Comparar;
	FuncaoCopiar = &TLivro_Copiar;
	Ordenador = TOrdenador_Criar(Sistema->NomeTemp, FuncaoComparar, FuncaoCopiar, Sistema->MaxItensMemoria);
	Livro = TLivro_Criar();
	if (!Livro)
	{
		TOrdenador_Destruir(&Ordenador);
		return false;
	}
	Livro->Titulo[0] = '_';
	Livro->Titulo[1] = '\0';
	Ordenador->LimiteInferior = Livro;
	Livro = TLivro_Criar();
	if (!Livro)
	{
		TLivro_Destruir((TLivro**)&Ordenador->LimiteInferior);
		TOrdenador_Destruir(&Ordenador);
		return false;
	}
	for (i = 0; i < 50; i++)
		Livro->Titulo[i] = 'z';
	Livro->Titulo[50] = '\0';
	Ordenador->LimiteSuperior = Livro;
	Ordenador->TamRegistro = sizeof(TLivro);
	Ordenador->Quantidade = Sistema->QuantLivros;
	TOrdenador_Ordenar(Ordenador);
	TLivro_Destruir((TLivro**)&Ordenador->LimiteInferior);
	TLivro_Destruir((TLivro**)&Ordenador->LimiteSuperior);
	TOrdenador_Destruir(&Ordenador);
	
	return true;
}

void TSistema_ProcessarConsultas(TSistema* Sistema)
{
	TSistemaConsulta* Consulta;

	while (TFila_Tamanho(Sistema->Consultas) > 0)
	{
		Consulta = TFila_Desenfileirar(Sistema->Consultas);
		TSistema		
		TSistema_Consulta(&Consulta);
	}
}

bool TSistema_ReceberConsultas(TSistema* Sistema, unsigned long NumConsultas)
{
	unsigned long i;
	char nomelivro[51];
	TSistemaConsulta* Consulta;
	
	Sistema->Consultas = TFila_Criar(NumConsultas);
	if (!Sistema->Consultas)
		return false;
	for (i = 0; i < NumConsultas; i++)
	{
		if (scanf("%50s", nomelivro) > 0)
		{
			Consulta = TSistemaConsulta_Criar(nomelivro);
			if (!TFila_Enfileirar(Sistema->Consultas, Consulta))
				return false;
			getchar();		
		}
		else
		{
			printf("Erro ao processar consulta (%lu de %lu).\n", i+1, NumConsultas);
			return false;
		}
	}
	
	return true;
}

bool TSistema_ReceberEntrada(TSistema* Sistema)
{
	unsigned long numconsultas;

	if (scanf("%lu %lu %lu %lu %lu", &Sistema->QuantLivros, &Sistema->MaxItensMemoria, &Sistema->QuantEstantes, &Sistema->QuantLivrosEstantes, &numconsultas) > 0)
	{
		getchar();
		return TSistema_ReceberLivros(Sistema) && TSistema_ReceberConsultas(Sistema, numconsultas);
	}
	else
	{
		perror("Erro ao processar entrada de variáveis.\n");
		return false;
	}
}

bool TSistema_ReceberLivros(TSistema* Sistema)
{
	unsigned long i;
	TSistemaManipuladorES* Livros;
	TLivro* Livro;

	Livros = TSistemaManipuladorES_Criar(Sistema->NomeTemp, esmBinarioEscrita);
	if (!Livros)
	{
		printf("Erro ao criar arquivo temporário.\n");
		return false;
	}
	Livro = TLivro_Criar();
	memset(Livro, 0, sizeof(TLivro));
	if (!Livro)
	{
		TSistemaManipuladorES_Destruir(&Livros);
		return false;
	}
	for (i = 0; i < Sistema->QuantLivros; i++)
	{
		if (scanf("%50s %c", Livro->Titulo, &Livro->Disponivel) > 0)
		{
			if (!TSistemaManipuladorES_ExportarFinal(Livros, Livro, sizeof(TLivro)))
			{
				TSistemaManipuladorES_Destruir(&Livros);
				TLivro_Destruir(&Livro);
				perror("Erro ao salvar livro em arquivo temporário.\n");
				return false;		
			}
		}
		else
		{
			TSistemaManipuladorES_Destruir(&Livros);
			TLivro_Destruir(&Livro);
			printf("Erro ao processar entreda de livros (%lu de %lu).\n", i+1, Sistema->QuantLivros);
			return false;
		}
	}
	TSistemaManipuladorES_Destruir(&Livros);
	TLivro_Destruir(&Livro);

	return true;
}

bool TSistema_SalvarLivros(TSistema* Sistema)
{
	unsigned long i, j = 0, numestante = 0;
	char nomeestante[1024], string[54], txtindice[103];
	int tamtitulo, tamtxtindice;
	TLivro* Livro;
	TSistemaManipuladorES* Estante;
	TSistemaManipuladorES* Indice;
	TSistemaManipuladorES* LivrosBinario;
	TSistemaManipuladorES* LivrosTexto;

	Livro = TLivro_Criar();
	if (!Livro)
		return false;
	LivrosBinario = TSistemaManipuladorES_Criar(Sistema->NomeTemp, esmBinarioLeitura);
	if (!LivrosBinario)
	{
		printf("Erro ao acessar arquivo temporario.\n");
		TLivro_Destruir(&Livro);
		return false;
	}
	LivrosTexto = TSistemaManipuladorES_Criar(Sistema->NomeLivrosOrdenados, esmTextoEscrita);
	if (!LivrosTexto)
	{
		printf("Erro ao criar arquivo de livros.\n");
		TLivro_Destruir(&Livro);
		TSistemaManipuladorES_Destruir(&LivrosBinario);
		return false;
	}
	Indice = TSistemaManipuladorES_Criar(Sistema->NomeIndice, esmTextoEscrita);
	if (!Indice)
	{
		printf("Erro ao criar arquivo de indice.\n");
		TLivro_Destruir(&Livro);
		TSistemaManipuladorES_Destruir(&LivrosBinario);
		TSistemaManipuladorES_Destruir(&LivrosTexto);
		return false;
	}
	sprintf(nomeestante, "%s%lu", Sistema->NomeEstante, numestante);
	Estante = TSistemaManipuladorES_Criar(nomeestante, esmBinarioEscrita);
	if (!Estante)
	{
		printf("Erro ao criar arquivo da estante 0.\n");
		TLivro_Destruir(&Livro);
		TSistemaManipuladorES_Destruir(&Indice);
		TSistemaManipuladorES_Destruir(&LivrosBinario);
		TSistemaManipuladorES_Destruir(&LivrosTexto);
		return false;
	}
	memset(txtindice, 0, 102);
	for (i = 0; i < Sistema->QuantLivros; i++)
	{
		if (i / Sistema->QuantLivrosEstantes > numestante)
		{
			TSistemaManipuladorES_Destruir(&Estante);
			numestante++;
			sprintf(nomeestante, "%s%lu", Sistema->NomeEstante, numestante);
			Estante = TSistemaManipuladorES_Criar(nomeestante, esmBinarioEscrita);
			j = 0;
		} 
		TSistemaManipuladorES_ImportarProximo(LivrosBinario, Livro, sizeof(TLivro));
		TSistemaManipuladorES_ExportarFinal(Estante, Livro, sizeof(TLivro));
		strcpy(string, Livro->Titulo);
		if (j == 0)
			strcpy(txtindice, Livro->Titulo);
		else if (j == Sistema->QuantLivrosEstantes - 1)
		{
			strcat(txtindice, " ");
			strcat(txtindice, Livro->Titulo);
			tamtxtindice = strlen(txtindice);
			txtindice[tamtxtindice] = '\n';
			TSistemaManipuladorES_ExportarFinal(Indice, txtindice, (tamtxtindice + 1) * sizeof(char));
		}
		tamtitulo = strlen(string);
		string[tamtitulo] = ' ';
		string[tamtitulo+1] = Livro->Disponivel;
		string[tamtitulo+2] = '\n';
		string[tamtitulo+3] = '\0';
		TSistemaManipuladorES_ExportarFinal(LivrosTexto, string, (tamtitulo + 3) * sizeof(char));
		j++;
	}
	if (j == 1)
	{
		tamtxtindice = strlen(txtindice);
		TSistemaManipuladorES_ExportarFinal(Indice, txtindice, tamtxtindice * sizeof(char));
	}
	while (++numestante < Sistema->QuantEstantes)
	{
		TSistemaManipuladorES_Destruir(&Estante);
		sprintf(nomeestante, "%s%lu", Sistema->NomeEstante, numestante);
		Estante = TSistemaManipuladorES_Criar(nomeestante, esmBinarioEscrita);
	}
	TSistemaManipuladorES_Destruir(&Estante);
	TSistemaManipuladorES_Destruir(&Indice);
	TSistemaManipuladorES_Destruir(&LivrosBinario);
	TSistemaManipuladorES_Destruir(&LivrosTexto);
	TLivro_Destruir(&Livro);

	return true;
}

void TSistema_Simular(TSistema* Sistema)
{
	/* 1a. parte -- ordenacao extrena */
	if (TSistema_OrdenarLivros(Sistema) && TSistema_SalvarLivros(Sistema)
		TSistema_ProcessarConsultas(Sistema);
	else
		perror("Erro ao ordenar livros.\n");
	remove(Sistema->NomeTemp);
}
