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

/* Cria um livro na memoria */
TLivro* TLivro_Criar(void);

/* Destroi um livro da memoria */
void TLivro_Destruir(TLivro** PLivro);

/* Compara dois livros, retornando verdadeiro se tiverem nomes iguais */
bool TLivro_Comparar(void* Livro1, void* Livro2);

/* Copia os dados de um livro para outro */
void TLivro_Copiar(void* Livro1, void* Livro2);
#endif
