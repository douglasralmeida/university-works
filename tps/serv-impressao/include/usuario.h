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

TUsuario* TUsuario_Criar(char* Nome, size_t Prioridade);

void TUsuario_Destruir(void** PUsuario);

bool TUsuario_Iguais(void* Usuario1, void* Usuario2);
#endif