#ifndef PROCESSADOR_H
#define PROCESSADOR_H

#include <limits.h>
#include "boolutils.h"
#include "caminho.h"
#include "list.h"
#include "grafo.h"

#define INFINITO UINT_MAX

typedef struct TProcessador_ {
	int Destino;
	TGrafo* Caminhos;
	int MelhorCaminho;
	TLista* Resultado;
	int Origem;
} TProcessador;

TProcessador* TProcessador_Criar();

void TProcessador_Destruir(TProcessador** PProcessador);

void TProcessador_AnalisarDados(TProcessador* Processador, char* NomeArquivo);

bool TProcessador_MelhorCaminho(TProcessador* Processador);

void TProcessador_OrdenarResultado(TProcessador* Processador);

void TProcessador_SalvarVetor(TProcessador* Processador, char* NomeArquivo);

#endif
