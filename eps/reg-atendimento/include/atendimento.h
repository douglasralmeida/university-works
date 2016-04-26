#ifndef ATENDIMENTO_H
#define ATENDIMENTO_H

#define BUFFER_TAMANHO 16 * 1024
#define CMD_NOVOCLIENTE 1
#define CMD_ATENDINICIO 2
#define CMD_ATENDCONCLU 3
#define CMD_DESISTENCIA 4
#define CMD_EXRELATORIO 5
#define CMD_SISTEMASAIR 6
#include "cliente.h"

typedef struct TAtendimento_ {
	unsigned int Atendidos;
	unsigned int Capacidade;
	TCliente* ListaClientes;
	unsigned int Quantidade;
} TAtendimento;

void BufferAnalisar(TAtendimento* Atendimento, char* Buffer, int Tamanho);
void AnalisarDados(int Descritor);
int EntradaLerCabecalho(char* Buffer);
void LinhaDoisStringsLer();
void LinhaTresStringsLer();

TAtendimento* AtendimentoCriar(int NovaCapacidade);
void AtendimentoDestruir(TAtendimento** PAtendimento);
void AtendimentoClienteAdicionar(TAtendimento* Atendimento, unsigned int ID, THora Chegada, float Valor);
void AtendimentoClienteAtender(TAtendimento* Atendimento, unsigned int ID, THora Hora);
void AtendimentoClienteConcluir(TAtendimento* Atendimento, unsigned int ID, THora Hora);
void AtendimentoClienteDesistencia(TAtendimento* Atendimento, unsigned int ID, THora Hora);
void AtendimentoProcessarDados(char* Arquivo);
#endif
