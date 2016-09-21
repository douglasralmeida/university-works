/*
**	BIBLIOTECA DO FILIPE
**	DOUGLAS RODRIGUES DE ALMEIDA
**
**	Estrutura de dados do tipo Livro
*/

#ifndef LIVRO_H
#define LIVRO_H

typedef struct _TLivro {
	char Titulo[51];
	char Disponivel;	
} TLivro;

TLivro* TLivro_Criar(char* Titulo, Disponivel);

void TLivro_Destruir(TLivro** PLivro);

#endif
