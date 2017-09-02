#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "recursos.h"
#include "funcoes.h"
#include "vetor.h"
#include "arquivo.h"

#define FALSE 0
#define TRUE 1
#define MAX_STRING 32

//Manipualar Arquivo
FILE* ArquivoAbrir(int Tipo, char* Nome)
{
	char* Caminho;
	FILE* NovoArquivo;
	
	Caminho = ReceberRecDirCompleto(Tipo, Nome);
	NovoArquivo = fopen(Caminho, "rt");
	free(Caminho);
	
	return NovoArquivo;
}

void ArquivoFechar(FILE* Arquivo)
{
	if (Arquivo != NULL)
		fclose(Arquivo);
}

//Nomes de secao
int SecaoChecar(char* Nome, FILE* Arquivo)
{
	int i;
	int resultado;
	char* temp_string;
	
	i = strlen(Nome);
	temp_string = (char*)malloc((i+1)*sizeof(char));
	if (temp_string == NULL)
	{
		ErroPadronizado(IDS_ERROMEMALOC);
		return FALSE;
	}
	if (fgets(temp_string, i+1, Arquivo))
		resultado = (strcmp(Nome, temp_string) == 0);
	else
		resultado = FALSE;
	fgetc(Arquivo);
	free(temp_string);
	
	return resultado;
}

int LerPropriedadeInteiro(char* Nome, int* Valor, FILE* Arquivo)
{
	char* temp_string;

	temp_string = (char*)malloc((MAX_STRING + 1)*sizeof(char));
	if (temp_string == NULL)
	{
		ErroPadronizado(IDS_ERROMEMALOC);
		return FALSE;
	}
	fscanf(Arquivo, "%32s %d", temp_string, Valor);
	fgetc(Arquivo);
	if (strcmp(Nome, temp_string) != 0)
	{
		free(temp_string);
		return FALSE;
	}
	free(temp_string);
	return TRUE;
}

int LerPropriedadePonto(char* Nome, TPonto* Valor, FILE* Arquivo)
{
	int x;
	int y;
	char* temp_string;

	temp_string = (char*)malloc((MAX_STRING + 1)*sizeof(char));
	if (temp_string == NULL)
	{
		ErroPadronizado(IDS_ERROMEMALOC);
		return FALSE;
	}	
	fscanf(Arquivo, "%32s %d %d", temp_string, &x, &y);
	
	fgetc(Arquivo);
	Valor->x = (float) x;
	Valor->y = (float) y;

	if (strcmp(Nome, temp_string) != 0)
	{
		free(temp_string);
		return FALSE;
	}
	free(temp_string);
	
	return TRUE;
}

int LerPropriedadeString(char* Nome, char* Valor, FILE* Arquivo)
{
	char* temp_string;
	
	temp_string = (char*)malloc((MAX_STRING + 1) * sizeof(char));
	if (temp_string == NULL)
	{
		ErroPadronizado(IDS_ERROMEMALOC);
		return FALSE;
	}	
	fscanf(Arquivo, "%32s %s", temp_string, Valor);
	fgetc(Arquivo);
	if (strcmp(Nome, temp_string) != 0)
	{		
		free(temp_string);
		return FALSE;
	}
	free(temp_string);

	return TRUE;	
}


int LerLinhaStr(char* resultado, FILE* Arquivo)
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
}

int LerLinhaDoisItensCI(char* resultado_char, int* resultado_int, FILE* Arquivo)
{
	char* temp_string;
	int temp_int;

	temp_string = (char*)malloc((MAX_STRING + 1)*sizeof(char));
	if (temp_string == NULL)
	{
		ErroPadronizado(IDS_ERROMEMALOC);
		return FALSE;
	}	
	fscanf(Arquivo, "%32s %d", temp_string, &temp_int);
	strcpy(resultado_char, temp_string);
	*resultado_int = temp_int;
	fgetc(Arquivo);
	free(temp_string);
	
	return TRUE;
}

int LerVetorStr(char** vetor, int num_itens, FILE* Arquivo)
{
	int i;
	for (i = 0; i < num_itens; i++)
	{
		LerLinhaStr(vetor[i], Arquivo);
	}
	return	 TRUE;
}

int** LerMatrizInt(int* num_linhas, int* num_col, FILE* Arquivo)
{
	int i; 
	int j;
	int x;
	int** matriz;
	char c;
	char temp_string[6];
	
	fscanf(Arquivo, "%d %d", num_linhas, num_col);
	fgetc(Arquivo);
	matriz = IMatrizCriar(*num_linhas, *num_col);
	if (matriz == NULL)
	{
		return NULL;
	}
	for (i = 0; i < *num_linhas; i++)
	{
		for (j = 0; j < *num_col; j++)
		{
			x = 0;
			do
			{
				c = fgetc(Arquivo);
				if (isdigit(c))
				{	
					temp_string[x] = c;
					x++;
				}
			} while (isdigit(c)  && (x < 5));
			temp_string[x] = '\0';
			matriz[i][j] = atoi(temp_string);
		}
	}
	return matriz;
}