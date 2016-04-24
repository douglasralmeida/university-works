#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "arquivo.h"

#define BUFFER_TAMANHO 16 * 1024

int LerCabecalho(char* Buffer)
{
	int Resultado;
	
	sscanf(Buffer, "%d", &Resultado);
	
	return Resultado;
}

void EntradaAnalisar(char* Buffer, int Tamanho)
{
	int Comando = 0;
	char* inicio;
	char* p = Buffer;
	char* q;

	p = (char*) memchr(p, '\n', (Buffer + Tamanho) - p);
	p++;
	while (Comando != 6)
	{	
		Comando = strtol(p, &q, 10);
		printf("Comando: %d\n", Comando);
		inicio = p;
		p = (char*) memchr(p, '\n', (Buffer + Tamanho) - p);
		switch (Comando)
		{
			case	1:
				/* sscanf(Buffer, "%s %s %s");*/
			break;
			case	2:
			case	3:
			case	4:
				/* sscanf(Buffer, "%s %s");*/
			break;
		}
		p++;
	}
}

void ArquivoAnalisar(int DescritorArquivo)
{	
	size_t BytesLidos;
	char Buffer[BUFFER_TAMANHO + 1];
	int LeuCabecalho = 0;
	int ArquivoChegouAoFim = 0;
	int j;
	
	/* Advise the kernel of our access pattern.  */
	posix_fadvise(DescritorArquivo, 0, 0, 1); /*FDADVICE_SEQUENTIAL*/
	while (!ArquivoChegouAoFim)
	{
		BytesLidos = read(DescritorArquivo, Buffer, BUFFER_TAMANHO);
		if (BytesLidos == (size_t) - 1)
		{
			printf("Erro ao acessar o arquivo de entrada.\n");
			ArquivoChegouAoFim = 1;
		}
		else if (!BytesLidos)
		{
			ArquivoChegouAoFim = 1;
		}
		else
		{
			if (!LeuCabecalho)
			{
				j = LerCabecalho(Buffer);
				printf("Quant: %d\n", j);
				LeuCabecalho = 1;
			}
			EntradaAnalisar(Buffer, BUFFER_TAMANHO);
		}
	}
}

int ArquivoAbrir(const char* Nome)
{
	return open(Nome, O_RDONLY);
}

void ArquivoFechar(int Descritor)
{
	close(Descritor);
}
/*
int ArquivoLerTipoLinha(FILE* Arquivo)
{
	int temp_int;

	fscanf(Arquivo, "%d", temp_int);
	fgetc(Arquivo);
	return temp_int;
}

int ArquivoLerLinha(char* resultado, FILE* Arquivo)
{
	char* temp_string;

	temp_string = (char*)malloc((MAX_STRING + 1)*sizeof(char));
	if (temp_string == NULL)
	{
		ErroPadronizado(IDS_ERROMEMALOC);
		return FALSE;
	}	
	fscanf(Arquivo, "%32s", temp_string);
	strcpy(resultado, temp_string);
	fgetc(Arquivo);
	free(temp_string);
	
	return TRUE;
}*/
