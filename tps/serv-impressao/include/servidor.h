/*
**	SERVIDOR DE IMPRESSSAO
**	DOUGLAS RODRIGUES DE ALMEIDA
**
**	info.
*/

#ifndef SERVIDOR_H
#define SERVIDOR_H

#include "boolutils.h"
#include "core.h"

#define BUFFER_TAMANHO 128

/* Usuario do sistema */
typedef struct _TServidor {
	FILE* ArquivoEntrada;
	FILE* ArquivoSaida;
	TImpressora* Impressora;
	TLista* Usuarios;
} TServidor;

TServidor* TServidor_Criar(void);

bool TServidor_CarregarEntrada(TServidor* Servidor, const char* Arquivo);

bool TServidor_Analisar(TServidor* Servidor);

bool TServidor_SalvarResultado(TServidor* Servidor, const char* Arquivo);

#endif