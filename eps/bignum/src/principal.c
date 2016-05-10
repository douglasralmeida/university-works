#include <stdio.h>
#include <stdlib.h>
#include "arquivo.h"
#include "bignum.h"

void ProcessarEntrada(const char* Arquivo)
{
	FILE* ArquivoEntrada;
	FILE* ArquivoSaida;
	
	TBigNum* NumeroA;
	TBigNum* NumeroB;
	TBigNum* NumeroR;
	
	ArquivoEntrada = ArquivoAbrirLeitura(Arquivo);
	if (ArquivoEntrada == NULL)
	{
		printf("Erro: Erro ao abrir arquivo de entrada.\n");
		return;
	}
	ArquivoSaida = ArquivoAbrirEscrita("ep2.out");
	if (ArquivoSaida == NULL)
	{
		printf("Erro: Erro ao abrir arquivo de saida.\n");
		return;
	}
	TBigNum_CarregarDeArquivo(NumeroA, ArquivoEntrada);
	TBigNum_CarregarDeArquivo(NumeroB, ArquivoEntrada);	
	NumeroR = TBigNum_Somar(NumeroA, NumeroB);
	TBigNum_SalvarNoArquivo(NumeroR, ArquivoSaida);
	
	TBigNum_Destruir(&NumeroA);
	TBigNum_Destruir(&NumeroB);
	TBigNum_Destruir(&NumeroR);
	
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
		printf("Erro: Erro na linha de comando informada.\n");
	}
	exit(EXIT_SUCCESS);
}
