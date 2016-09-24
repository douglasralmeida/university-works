/*
**	BIBLIOTECA DO FILIPE
**	DOUGLAS RODRIGUES DE ALMEIDA
**
**	Implementação do tipo Livro
*/

#include <stdio.h>
#include <stdlib.h>
#include "livro.h"

TLivro* TLivro_Criar()
{
	TLivro* NovoLivro;

	NovoLivro = malloc(sizeof(TLivro));
	if (!NovoLivro)
		return NULL;
	NovoLivro->Titulo[0] = '\0';
	NovoLivro->Disponivel = 0;

	return NovoLivro;
}

void TLivro_Destruir(TLivro** PLivro)
{
	free(*PLivro);
	*PLivro = NULL;
}
