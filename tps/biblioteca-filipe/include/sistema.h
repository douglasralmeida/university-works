/*
**	BIBLIOTECA DO FILIPE
**	DOUGLAS RODRIGUES DE ALMEIDA
**
**	Estrutura de dados do sistema da biblioteca
*/

#ifndef SISTEMA_H
#define SISTEMA_H

#include "fila.h"

typedef struct _TSistema {
	TFila* Consultas;
	size_t MaxItensMemoria;
	unsigned long QuantLivros;
} TSistema;

TSistema* TSistema_Criar(void);

void TSistema_Destruir(TSistema** PSistema);

void TSistema_LerEntrada(TSistema* Sistema);

void TSistema_OrdenarLivros(TSistema* Sistema);

void TSistema_SalvarLivros(TSistema* Sistema, char* NomeArquivo);

void TSistema_Simular(TSistema* Sistema);

#endif
