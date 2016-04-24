#ifndef ATENDIMENTO_H
#define ATENDIMENTO_H

#include "cliente.h"

typedef struct TAtendimento_ {
	unsigned int Atendidos;
	unsigned int Capacidade;
	TCliente* ListaClientes;
	unsigned int Quantidade;
} TAtendimento;

TAtendimento* AtendimentoCriar(int NovaCapacidade);
void AtendimentoDestruir(TAtendimento** PAtendimento);

#endif