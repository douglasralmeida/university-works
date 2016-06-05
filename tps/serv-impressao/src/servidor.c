{/*
**	SERVIDOR 
**	DOUGLAS RODRIGUES DE ALMEIDA
**
**	Implementacao do servidor
*/

#include "servidor.h"

bool TServidor_Analisar(TServidor* Servidor)
{
	char Buffer[BUFFER_TAMANHO + 1];
	
	/* Ler primeira linha com cadastro da impressora */
	if (fgets(Buffer, BUFFER_TAMANHO, TServidor->ArquivoEntrada) != NULL)
	{
		if (BufferImpressora(Servidor, Buffer))
		{
			
		}
	}
}

bool TServidor_CadastrarImpressora(TServidor* Servidor, char* Impressora, int Capacidade, int Escalonador)
{
	Servidor->Impressora = malloc(sizeof(TServidor));
	if (Servidor->Impressora == NULL)
		return false;
	
	strcpy(Servidor->Impressora->Nome, Impressora);
	Servidor->Impressora->Capacidade = Capacidade;
	Servidor->Impressora->Escalonador = Escalonador;
	
	return true;
}

bool TServidor_Finalizar(TServidor* Servidor)
{
	ArquivoFechar(Servidor->ArquivoEntrada);
	ArquivoFechar(Servidor->ArquivoSaida);
}

bool TServidor_Preparar(TServidor* Servidor, const char* NomeArquivoEntrada, const char* NomeArquivoSaida)
{
	Servidor->ArquivoEntrada = ArquivoAbrirLeitura(NomeArquivoEntrada);
	Servidor->ArquivoSaida = ArquivoAbrirEscrita(NomeArquivoSaida);
	
	return ((Servidor->AbrirEntrada != NULL) && (Servidor->ArquivoSaida != NULL));
}