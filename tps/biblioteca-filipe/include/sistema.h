/*
**	BIBLIOTECA DO FILIPE
**	DOUGLAS RODRIGUES DE ALMEIDA
**
**	Estrutura de dados do sistema da biblioteca
*/

#ifndef SISTEMA_H
#define SISTEMA_H

#include "memoria.h"

typedef struct _TSistema {
	
} TSistema;

TSistema* TSistema_Criar(void);

void TSistema_Destruir(TSistema** PSistema);

void TSistema_LerEntrada(void);

#endif
