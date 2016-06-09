/*
**	SERVIDOR DE IMPRESSSAO
**	DOUGLAS RODRIGUES DE ALMEIDA
**
**	info.
*/

#ifndef SERVIDOR_H
#define SERVIDOR_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "boolutils.h"
#include "core.h"
#include "list.h"
#include "servidor_impressora.h"
#include "servidor_relatorio.h"
#include "servidor_usuario.h"

#define BUFFER_TAMANHO 128
#define QUANT_PRIORIDADES 5

/* Usuario do sistema */
typedef struct _TServidor {
	FILE* ArquivoEntrada;
	FILE* ArquivoSaida;
	TImpressora* Impressora;
	TRelatorio* Relatorio;
	TLista* Usuarios;
} TServidor;

TServidor* TServidor_Criar(void);

void TServidor_Destruir(TServidor** PServidor);

bool TServidor_Analisar(TServidor* Servidor);

bool TServidor_CadastrarImpressora(TServidor* Servidor, char* Impressora, const int Capacidade, const int Escalonador);

bool TServidor_ChecarImpressao(TServidor* Servidor, TImpressao* Impressao);

void TServidor_FinalizaFila(TServidor* Servidor);

void TServidor_Finalizar(TServidor* Servidor);

bool TServidor_Preparar(TServidor* Servidor, const char* NomeArquivoEntrada, const char* NomeArquivoSaida);

void TServidor_ProcessarImpressao(TServidor* Servidor);

void TServidor_RecebeImpressao(TServidor* Servidor, TImpressao* Impressao);

void TServidor_Relatorio(TServidor* Servidor);

void TServidor_UsuarioExcluir(TServidor* Servidor, const char* Nome);

void TServidor_UsuarioNovo(TServidor* Servidor, const char* nome, const int Prioridade);
#endif
