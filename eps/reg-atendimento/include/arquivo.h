#ifndef ARQUIVO_H
#define ARQUIVO_H

#include <stdlib.h>

FILE* ArquivoAbrirLeitura(const char* Nome);

FILE* ArquivoAbrirEscrita(const char* Nome);

void ArquivoFechar(FILE* Arquivo);

#endif
