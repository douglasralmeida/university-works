#ifndef ATENDIMENTO_H
#define ATENDIMENTO_H

#include "cliente.h"

typedef struct TAtendimento_ {
	unsigned int Atendidos;
	unsigned int Capacidade;
	TCliente* ListaClientes;
	unsigned int Quantidade;
} TAtendimento;

void AnalisarBuffer();
void AnalisarDados(int Descritor);
void CabecalhoLer();
void LinhaDoisStringsLer();
void LinhaTresStringsLer();

TAtendimento* AtendimentoCriar(int NovaCapacidade);
void AtendimentoDestruir(TAtendimento** PAtendimento);
void AtendimentoProcessarDados(char* Arquivo);
#endif
