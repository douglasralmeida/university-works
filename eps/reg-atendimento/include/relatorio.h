#ifndef RELATORIO_H
#define RELATORIO_H

#include "cliente.h"
#include "atendimento.h"

void ExibirMedias(FILE* Arquivo, TCliente* ListaClientes, int Quantidade);
void ExibirRelatorio(TAtendimento* Atendimento);
void GravarHora(FILE*Arquivo, THora Hora);
#endif
