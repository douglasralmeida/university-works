#include <sys/stat.h>
#include <unistd.h>
#include "arquivo.h"

int ArquivoAbrir(const char* Nome)
{
	return open(Nome, O_RDONLY);
}

void ArquivoFechar(int Descritor)
{
	close(Descritor);
}