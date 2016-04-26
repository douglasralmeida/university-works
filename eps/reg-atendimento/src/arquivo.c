#include <stdio.h>
#include "arquivo.h"

FILE* ArquivoAbrir(const char* Nome)
{
	return fopen(Nome , "rt");
}

void ArquivoFechar(FILE* Arquivo)
{
	fclose(Arquivo);
}
