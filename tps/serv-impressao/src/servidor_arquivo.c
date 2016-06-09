#include <stdio.h>
#include "servidor.h"
#include "servidor_arquivo.h"

int BufferAnalisar(TServidor* Servidor, char* Buffer)
{
	int comando;
	int encerrar = 0;
	int paginas, prioridade, tempo, inteiro;
	char texto[21];
	TImpressao* Impressao;
	TUsuario* Usuario;

	/* primeiro item da linha: comando */
	comando = Buffer[0] - '0';
	switch (comando)
	{
		case	CMD_USUARIONOVO:
			sscanf(Buffer, "%*d %20s %d", &texto[0], &inteiro);
			TServidor_UsuarioNovo(Servidor, texto, inteiro);
		break;
		case	CMD_USUARIOEXCLUIR:
			sscanf(Buffer, "%*d %20s", &texto[0]);
			TServidor_UsuarioExcluir(Servidor, texto);
		break;
		case	CMD_RELATORIO:
			sscanf(Buffer, "%d", &inteiro);
			TServidor_Relatorio(Servidor);
		break;
		case	CMD_IMPRIMIR:
			sscanf(Buffer, "%*d %d %20s %d %d %d", &inteiro, &texto[0], &prioridade, &paginas, &tempo);
			Usuario = TUsuario_Criar(texto, 0);
			Impressao = TImpressao_Criar(Usuario, inteiro, prioridade, paginas, tempo);
			TServidor_RecebeImpressao(Servidor, Impressao);
		break;
		case	CMD_SAIR:
			encerrar = 1;
		break;
	}
	return encerrar;
}

bool BufferImpressora(TServidor* Servidor, char* Buffer)
{
	char impressora[11];
	int capacidade;
	int escalonador;
	
	sscanf(Buffer, "%10s %d %d", &impressora[0], &capacidade, &escalonador);
	return TServidor_CadastrarImpressora(Servidor, impressora, capacidade, escalonador);
}
