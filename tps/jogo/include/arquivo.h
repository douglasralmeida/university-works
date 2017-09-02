#ifndef _ARQUIVO_H_
#define _ARQUIVO_H_

#include <stdio.h>
#include "tipos.h"

FILE* ArquivoAbrir(int Tipo, char* Nome);
void ArquivoFechar(FILE* Arquivo);
int SecaoChecar(char* Nome, FILE* Arquivo);
int LerPropriedadeInteiro(char* Nome, int* Valor, FILE* Arquivo);
int LerPropriedadePonto(char* Nome, TPonto* Valor, FILE* Arquivo);
int LerPropriedadeString(char* Nome, char* Valor, FILE* Arquivo);
int LerLinhaStr(char* resultado, FILE* Arquivo);
int LerLinhaDoisItensCI(char* resultado_char, int* resultado_int, FILE* Arquivo);
int LerVetorStr(char** vetor, int num_itens, FILE* Arquivo);
int** LerMatrizInt(int* num_linhas, int* num_col, FILE* Arquivo);

#endif
