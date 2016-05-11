/*
**	EXERCICIO PRATICO 2 DE AEDS 2
**	DOUGLAS RODRIGUES DE ALMEIDA
**
**	Algoritmos e Estrutura de Dados para manipulacao de inteiros de tamanho arbitrario
**	
**/

#include <stdio.h>
#include <stdlib.h>
#include "arquivo.h"
#include "bignum.h"

void ProcessarEntrada(const char* Arquivo)
{
	int soma;
	FILE* ArquivoEntrada;
	FILE* ArquivoSaida;
	TBigNum* NumeroA;
	TBigNum* NumeroB;
	TBigNum* NumeroR;
	
	soma = 0;
	ArquivoEntrada = ArquivoAbrirLeitura(Arquivo);
	if (ArquivoEntrada == NULL)
	{
		printf("Erro(0x52): Erro ao abrir arquivo de entrada.\n");
		return;
	}
	ArquivoSaida = ArquivoAbrirEscrita("ep2.out");
	if (ArquivoSaida == NULL)
	{
		printf("Erro(0x53): Erro ao abrir arquivo de saida.\n");
		return;
	}
	NumeroA = TBigNum_Criar();
	NumeroB = TBigNum_Criar();
	if (!TBigNum_CarregarDeArquivo(NumeroA, ArquivoEntrada))
	{
		printf("Erro(0x54): Formato de arquivo irreconhecivel.\n");
		TBigNum_Destruir(&NumeroA);
		TBigNum_Destruir(&NumeroB);
		return;
	}
	if (!TBigNum_CarregarDeArquivo(NumeroB, ArquivoEntrada))
	{
		printf("Erro(0x54): Formato de arquivo irreconhecivel.\n");
		TBigNum_Destruir(&NumeroA);
		TBigNum_Destruir(&NumeroB);
		return;
	}
	while (!((TBigNum_EZero(NumeroA)) && (TBigNum_EZero(NumeroB))))
	{
		if (soma)
			NumeroR = TBigNum_Somar(NumeroA, NumeroB);
		else
			NumeroR = TBigNum_Subtrair(NumeroA, NumeroB);
		if (!TBigNum_SalvarNoArquivo(NumeroR, ArquivoSaida))
			printf("Erro(0x55): Erro ao salvar dados no arquivo de saida\n");
		fprintf(ArquivoSaida, "\n");
		TBigNum_Destruir(&NumeroR);
		soma = !soma;
		if (!TBigNum_CarregarDeArquivo(NumeroA, ArquivoEntrada))
		{
			printf("Erro(0x54): Formato de arquivo irreconhecivel.\n");
			TBigNum_Destruir(&NumeroA);
			TBigNum_Destruir(&NumeroB);
			return;
		}
		if (!TBigNum_CarregarDeArquivo(NumeroB, ArquivoEntrada))
		{
			printf("Erro(0x54): Formato de arquivo irreconhecivel.\n");
			TBigNum_Destruir(&NumeroA);
			TBigNum_Destruir(&NumeroB);
			return;
		}		
	}
	TBigNum_Destruir(&NumeroA);
	TBigNum_Destruir(&NumeroB);
	ArquivoFechar(ArquivoEntrada);
	ArquivoFechar(ArquivoSaida);	
}

int main(int argc, char *argv[])
{	
	if (argc > 1)
	{
		ProcessarEntrada(argv[1]);
	}
	else
	{
		printf("Erro(0x51): Erro na linha de comando informada.\n");
	}
	exit(EXIT_SUCCESS);
}
