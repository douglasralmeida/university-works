#include <stdio.h>
#include "servidor.h"
#include "servidor_arquivo.h"

int BufferAnalisar(TServidor* Servidor, char* Buffer)
{
	int comando;
	int encerrar = 0;
	int paginas, prioridade, tempo, inteiro;
	char[21] texto;

	/* primeiro item da linha: comando */
	comando = Buffer[0] - '0';
	switch (comando)
	{
		case	CMD_USUARIONOVO:
			sscanf(Buffer, "%*d %20s %d", &texto, &inteiro);
			TServidor_UsuarioNovo(Servidor, texto, inteiro);
		break;
		case	CMD_USUARIOEXCLUIR:
			sscanf(Buffer, "%*d %20s", texto);
			TServidor_UsuarioExcluir(Servidor, texto);
		break;
		case	CMD_RELATORIO:
			sscanf(Buffer, "%d", inteiro);
			TServidor_Relatorio(Servidor);
		break;
		case	CMD_IMPRIMIR:
			sscanf(Buffer, "%*d %d %20s %d %d %d", &inteiro, texto, &prioridade, &paginas, &tempo);
			TServidor_Imprimir(Servidor, texto, inteiro, prioridade, paginas, tempo);
		break;
		case	CMD_SAIR:
			encerrar = 1;
		break;
	}
	return encerrar;
}

bool BufferImpressora(TServidor* Servidor, char* Buffer)
{
	char[11] impressora;
	int capacidade;
	int escalonador;
	
	sscanf(Buffer, "%10s %d %d", impressora, &capacidade, &escalonador);
	return Servidor_CadastrarImpressora(Servidor, impressora, capacidade, escalonador);
}