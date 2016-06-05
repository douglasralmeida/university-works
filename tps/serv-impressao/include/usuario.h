/*
**	TIPO ABSTRATO DE DADOS USUARIO
**	DOUGLAS RODRIGUES DE ALMEIDA
**
**	Cadastro dos usuarios do sistemas
*/

#ifndef USUARIO_H
#define USUARIO_H

#include "boolutils.h"
#include "core.h"

/* Usuario do sistema */
typedef struct _TUsuario {
	char[11] Nome;
	size_t Prioridade;
} TUsuario;

#endif