#include <stdlib.h>
#include "atendimento.h"

void AnalisarDados(int Descritor)
{
	
}

TAtendimento* AtendimentoCriar(int NovaCapacidade)
{
	TAtendimento* NovoAtendimento;
	
	NovoAtendimento = malloc(sizeof(TAtendimento));
	NovoAtendimento->Atendidos = 0;
	NovoAtendimento->Capacidade = NovaCapacidade;
	NovoAtendimento->ListaClientes = malloc(sizeof(TCliente) * NovaCapacidade);
	NovoAtendimento->Quantidade = 0;
	
	return NovoAtendimento;
}

void AtendimentoDestruir(TAtendimento** PAtendimento)
{
	free((*PAtendimento)->ListaClientes);
	free(*PAtendimento);
	*PAtendimento = NULL;
}

void AtendimentoProcessarDados(char* Arquivo)
{
	int DescritorArquivo;

	DescritorArquivo = ArquivoAbrir(Arquivo);
	if (DescritorArquivo != -1)
	{
		AnalisarDados(DescritorArquivo);
		ArquivoFechar(DescritorArquivo);
	}
	else
	{
		prinf("Erro ao abrir arquivo de entrada de dados.\n");
	}
}
