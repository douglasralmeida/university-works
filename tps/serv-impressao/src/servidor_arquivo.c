#include <stdio.h>
#include "servidor.h"
#include "servidor_arquivo.h"

bool BufferImpressora(TServidor* Servidor, char* Buffer)
{
	char[11] impressora;
	int capacidade;
	int escalonador;
	
	sscanf(Buffer, "%10s %d %d", impressora, &capacidade, &escalonador);
	return Servidor_CadastrarImpressora(Servidor, impressora, capacidade, escalonador);
}