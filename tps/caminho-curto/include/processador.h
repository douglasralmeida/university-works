#ifndef PROCESSADOR_H
#define PROCESSADOR_H

#include "boolutils.h"
#include "list.h"
#include "grafo.h"

typedef struct TProcessador_ {
	TGrafo* Caminhos;
} TProcessador;

TProcessador* TProcessador_Criar();

void TProcessador_Destruir(TProcessador** PProcessador);

void TProcessador_AnalisarDados(TProcessador* Processador);

bool TProcessador_CarregarDados(TProcessador* Processador, char* NomeArquivo);

bool TProcessador_MelhorCaminho(TProcessador* Processador);

void TProcessador_OrdenarResultado(TProcessador* Processador);

bool TProcessador_SalvarResultado(TProcessador* Processador, char* NomeArquivo);

#endif
