#include <stdlib.h>
#include "atendimento.h"

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
