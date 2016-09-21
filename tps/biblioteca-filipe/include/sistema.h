/*
**	BIBLIOTECA DO FILIPE
**	DOUGLAS RODRIGUES DE ALMEIDA
**
**	Estrutura de dados do sistema da biblioteca
*/

#ifndef SISTEMA_H
#define SISTEMA_H

#include "fila.h"
#include "memoria.h"
#include "arquivo.h"

typedef struct _TSistema {
	TArquivo* LivrosOrdenados;
	TFila* Consultas;
} TSistema;

TSistema* TSistema_Criar(void);

void TSistema_Destruir(TSistema** PSistema);

void TSistema_LerEntrada(TSistema* Sistema);

#endif
