#include "cliente.h"

void ClienteLimpar(TCliente* Cliente)
{
	Cliente->Gasto = 0.0;
	Cliente->Chegada = 0;
	Cliente->AtendimentoInicio = 0;
	Cliente->Saida = 0;
	Cliente->Desistencia = 0;
	Cliente->Vazio = 1;
}

int ClienteMinutosAtendimento(TCliente* Cliente)
{
	return HoraParaMinutos(Cliente->Saida) - HoraParaMinutos(Cliente->AtendimentoInicio);
}

int ClienteMinutosEspera(TCliente* Cliente)
{
	return HoraParaMinutos(Cliente->AtendimentoInicio) - HoraParaMinutos(Cliente->Chegada);
}

int ClienteMinutosTotal(TCliente* Cliente)
{
	return HoraParaMinutos(Cliente->Saida) - HoraParaMinutos(Cliente->Chegada); 
}


