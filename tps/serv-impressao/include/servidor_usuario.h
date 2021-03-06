/*
**	SERVIDOR DE IMPRESSSAO
**	DOUGLAS RODRIGUES DE ALMEIDA
**
**	TAD auxiliar para cadastro de usuarios no sistema
*/

#ifndef USUARIO_H
#define USUARIO_H

#include <string.h>	
#include "boolutils.h"
#include "core.h"

/* Usuario do sistema */
typedef struct _TUsuario {
	char Nome[22];
	int Prioridade;
} TUsuario;

TUsuario* TUsuario_Criar(const char* Nome, const int Prioridade);

void TUsuario_Destruir(void** PUsuario);

bool TUsuario_Iguais(void* Usuario1, void* Usuario2);
#endif
