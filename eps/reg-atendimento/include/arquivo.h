#ifndef ARQUIVO_H
#define ARQUIVO_H

#include <stdlib.h>

int LerCabecalho(char* Buffer);

void EntradaAnalisar(char* Buffer, int Tamanho);

void ArquivoAnalisar(int DescritorArquivo);

int ArquivoAbrir(const char* Nome);

void ArquivoFechar(int Descritor);

#endif
