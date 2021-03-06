#ifndef PROCESSADOR_H
#define PROCESSADOR_H

#include "boolutils.h"
#include "caminho.h"
#include "list.h"
#include "grafo.h"

typedef struct TProcessador_ {
	unsigned int Destino;
	TGrafo* Caminhos;
	int MelhorCaminho;
	TLista* Resultado;
	unsigned int Origem;
} TProcessador;

TProcessador* TProcessador_Criar();

void TProcessador_Destruir(TProcessador** PProcessador);

void TProcessador_AnalisarDados(TProcessador* Processador, char* NomeArquivo);

void TProcessador_MelhorCaminho(TProcessador* Processador);

void TProcessador_OrdenarResultado(TProcessador* Processador);

void TProcessador_SalvarVetor(TProcessador* Processador, char* NomeArquivo);

#endif
