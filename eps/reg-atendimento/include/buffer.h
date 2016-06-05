#ifndef BUFFER_H
#define BUFFER_H

#include <stdlib.h>

FILE* BufferImpressora(TServidor* Servidor, char* Buffer);

FILE* ArquivoAbrirEscrita(const char* Nome);

void ArquivoFechar(FILE* Arquivo);

#endif
