/*
**	TIPO ABSTRATO DE DADOS USUARIO
**	DOUGLAS RODRIGUES DE ALMEIDA
**
**	Cadastro dos usuarios do sistemas
*/

#ifndef IMPRESSORA_H
#define IMPRESSORA_H

#include "boolutils.h"
#include "core.h"

/* Usuario do sistema */
typedef struct _TImpressora {
	char[11] Nome;
	size_t Capacidade;
	size_t Escalonador;
	TFilaPrioridade FilaImpressao;
} TUsuario;

void TImpressora_Imprimir();

#endif