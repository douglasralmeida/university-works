/*
**	TAD BIGNUM
**	DOUGLAS RODRIGUES DE ALMEIDA
**
**	Cabecalhos e estruturas do TAD para manipulacao de inteiros de tamanho arbitrario
**	
**/

#ifndef BIGNUM_H
#define BIGNUM_H

#include <stdio.h>
#include <stdlib.h>
#include "sysutils.h"
#include "list.h"

/* Estrutura do TAD Bignum */
typedef struct TBigNum_ {
	TLista* Algarismos;
	} TBigNum;

/* Cria um numero na memoria */
TBigNum* TBigNum_Criar();

/* Destroi um numero */
void TBigNum_Destruir(TBigNum** PBigNum);

/* Apaga todos os algarimos igual a zero a esquerda */
void TBigNum_ApagarZeroEsquerda(TBigNum* Numero);

/* Carrega um numero de um arquivo */
bool TBigNum_CarregarDeArquivo(TBigNum* Numero, FILE* Arquivo);

/* Compara dois numeros */
TRelacao TBigNum_Comparar(TBigNum* NumeroX, TBigNum* NumeroY);

/* Checa se o numero e igual a zero */
bool TBigNum_EZero(TBigNum* Numero);

/* Imprime um numero na tela */
void TBigNum_Imprimir(TBigNum* Numero);

/* Grava um numero em um arquivo */
bool TBigNum_SalvarNoArquivo(TBigNum* Numero, FILE* Arquivo);

/* Soma dois numeros */
TBigNum* TBigNum_Somar(TBigNum* NumeroX, TBigNum* NumeroY);

/* Subtrai dois numeros */
TBigNum* TBigNum_Subtrair(TBigNum* NumeroX, TBigNum* NumeroY);

/* Retorna o numero de algarismos do numero */
unsigned int TBigNum_Tamanho(TBigNum* Numero);

#endif
