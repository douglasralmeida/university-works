/*
**	BIGNUM
**	DOUGLAS RODRIGUES DE ALMEIDA
**
**	Cabecalho do TAD Bignum
**	
**/

#ifndef BIGNUM_H
#define BIGNUM_H

#include <stdio.h>
#include <stdlib.h>
#include "list.h"

typedef struct TBigNum_ {
	TLista* Algarismos;
	} TBigNum;

/* Cria um numero na memoria */
TBigNum* TBigNum_Criar();

/* Destroi um numero */
void TBigNum_Destruir(TBigNum** PBigNum);

/* Carrega um numero de um arquivo */
void TBigNum_CarregarDeArquivo(TBigNum* Numero, FILE* Arquivo);

/* Checa se o numero e igual a zero */
bool TBigNum_EZero(TBigNum* Numero);

/* Soma dois numeros */
TBigNum* TBigNum_Somar(TBigNum* NumeroX, TBigNum* NumeroY);

/* Subtrai dois numeros */
/*TBigNum* TBigNum_Subtrai(TBigNum* NumeroX, TBigNum* NumeroY);*/

/* Grava um numero em um arquivo */
void TBigNum_SalvarNoArquivo(TBigNum* Numero, FILE* Arquivo);

/* Retorna o numero de algarismos do numero */
unsigned int TBigNum_Tamanho(TBigNum* Numero);

#endif
