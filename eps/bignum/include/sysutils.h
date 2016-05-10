#ifndef SYSUTILS_H
#define SYSUTILS_H

typedef enum {
	relacMenor, relacIgual, relacMaior
	} TRelacao;

/* Retorna o numero menor entre dois numeros */
unsigned short MenorValor(unsigned short a, unsigned short b);

#endif
