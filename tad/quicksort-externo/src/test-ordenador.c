/*
**	TESTE DO TAD ORDENADOR
**	DOUGLAS RODRIGUES DE ALMEIDA
**
**	Teste do TAD Ordenador
**	
**/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "boolutils.h"
#include "ordenador.h"

bool IntCompara(void* Int1, void* Int2)
{
	return (*(int*)Int1 < *(int*)Int2);
}

void IntCopia(void* Int1, void* Int2)
{
	*(int*)Int2 = *(int*)Int1;
}

int main(void)
{	
	int i;
	int* dado;
	char* NomeArquivo;
	FILE* Arquivo;
	TFuncaoComparar FuncaoCompara;
	TFuncaoCopiar FuncaoCopia;
	TOrdenador* Ordenador;
		
	printf("TESTE ORDENADOR EXTERNO\n");
	printf("=======================\n");
	FuncaoCompara = &IntCompara;
	FuncaoCopia = &IntCopia;
	NomeArquivo = "massadados";
	
	printf("Gerando arquivo...");
	srand(time(NULL));
	Arquivo = fopen(NomeArquivo, "wb");
	dado = malloc(sizeof(int));

	for (i = 0; i < 20; i++)
	{
		*dado = rand() % 100;
		printf("%d ", *dado);
		fwrite(dado, sizeof(int), 1, Arquivo);
	}
	free(dado);
	fflush(Arquivo);
	fclose(Arquivo);
	printf("OK.\n");

	printf("Criando ordenador...");
	Ordenador = TOrdenador_Criar(NomeArquivo, FuncaoCompara, FuncaoCopia, 3);
	if (Ordenador != NULL)
		printf("OK.\n");
	else
		exit(EXIT_FAILURE);
	dado = malloc(sizeof(int));
	*dado = 0;
	Ordenador->LimiteInferior = dado;
	dado = malloc(sizeof(int));
	*dado = 100;
	Ordenador->LimiteSuperior = dado;
	Ordenador->Quantidade = 20;
	Ordenador->TamRegistro = sizeof(int);

	printf("Ordenando...");
	TOrdenador_Ordenar(Ordenador);
	printf("OK.\n");
	
	printf("Destruindo ordenador...");
	free(Ordenador->LimiteInferior);
	free(Ordenador->LimiteSuperior);
	TOrdenador_Destruir(&Ordenador);
	printf("OK.\n");

	printf("Lendo o arquivo...");
	Arquivo = fopen(NomeArquivo, "rb");
	dado = malloc(sizeof(int));
 	while (fread(dado, sizeof(int), 1, Arquivo))
		printf("%d ", *dado);
	free(dado);
	fclose(Arquivo);
	printf("OK.\n");
	
	exit(EXIT_SUCCESS);
}
