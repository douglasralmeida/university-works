/*
**	BIBLIOTECA DO FILIPE
**	DOUGLAS RODRIGUES DE ALMEIDA
**
**	Estrutura de dados do sistema da biblioteca
*/

#ifndef SISTEMA_H
#define SISTEMA_H

#include "core.h"
#include "fila.h"

typedef struct _TSistema {
	TFila* Consultas;
	size_t MaxItensMemoria;
	char* NomeEstante;
	char* NomeIndice;
	char* NomeLivrosOrdenados;
	char* NomeTemp;
	unsigned long QuantEstantes;
	unsigned long QuantLivros;
	unsigned long QuantLivrosEstantes;
} TSistema;

TSistema* TSistema_Criar(void);

void TSistema_Destruir(TSistema** PSistema);

bool TSistema_OrdenarLivros(TSistema* Sistema);

void TSistema_ProcessarConsultas(TSistema* Sistema);

bool TSistema_ReceberConsultas(TSistema* Sistema, unsigned long NumConsultas);

bool TSistema_ReceberEntrada(TSistema* Sistema);

bool TSistema_ReceberLivros(TSistema* Sistema);

bool TSistema_SalvarLivros(TSistema* Sistema);

void TSistema_Simular(TSistema* Sistema);

#endif
