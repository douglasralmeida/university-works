/*
**	BIBLIOTECA DO FILIPE
**	DOUGLAS RODRIGUES DE ALMEIDA
**
**	Implementação do tipo Livro
*/

#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "livro.h"

TLivro* TLivro_Criar(void)
{
	TLivro* NovoLivro;

	NovoLivro = malloc(sizeof(TLivro));
	if (!NovoLivro)
		return NULL;
	NovoLivro->Titulo[0] = '\0';
	NovoLivro->Disponivel = '0';

	return NovoLivro;
}

void TLivro_Destruir(TLivro** PLivro)
{
	free(*PLivro);
	*PLivro = NULL;
}

bool TLivro_Comparar(void* Livro1, void* Livro2)
{
	return (strcmp((const char*)((TLivro*)Livro1)->Titulo, (const char*)((TLivro*)Livro2)->Titulo) < 0);
}

void TLivro_Copiar(void* Livro1, void* Livro2)
{
	TLivro* LivroOrigem;
	TLivro* LivroDestino;

	LivroOrigem = (TLivro*)Livro1;
	LivroDestino = (TLivro*)Livro2;

	LivroDestino->Disponivel= LivroOrigem->Disponivel;
	strcpy(LivroDestino->Titulo, LivroOrigem->Titulo);
}
