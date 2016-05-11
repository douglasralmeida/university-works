/*
**	FUNCOES UTILITARIAS
**	DOUGLAS RODRIGUES DE ALMEIDA
**
**	Cabecalho de funcoes com utilidade em futuros trabalhos
**	
**/

#ifndef SYSUTILS_H
#define SYSUTILS_H

/* Estrutura auxiliar usada em comparacoes */
typedef enum {
	relacMenor, relacIgual, relacMaior
	} TRelacao;

/* Retorna o numero menor entre dois numeros */
unsigned short MenorValor(unsigned short a, unsigned short b);

#endif
