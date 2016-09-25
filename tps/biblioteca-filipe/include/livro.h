/*
**	BIBLIOTECA DO FILIPE
**	DOUGLAS RODRIGUES DE ALMEIDA
**
**	Estrutura de dados do tipo Livro
*/

#ifndef LIVRO_H
#define LIVRO_H

#include "boolutils.h"
#include "strutils.h"

typedef struct _TLivro {
	char Titulo[51];
	char Disponivel;
} TLivro;

TLivro* TLivro_Criar(void);

void TLivro_Destruir(TLivro** PLivro);

bool TLivro_Comparar(void* Livro1, void* Livro2);

void TLivro_Copiar(void* Livro1, void* Livro2);
#endif
