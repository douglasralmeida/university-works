#ifndef BIGNUM_H
#define BIGNUM_H

#include "list.h"

typedef TBigNum_ {
	} TBigNum;

TBigNum* TBigNum_Criar();
void TBigNum_Destruir(TBigNum** PBigNum);
TBigNum* TBigNum_CarregarDeArquivo(FILE* Arquivo);
TBigNum* TBigNum_Soma(TBigNum* NumeroX, TBigNum* NumeroY);
TBigNum* TBigNum_Subtrai(TBigNum* NumeroX, TBigNum* NumeroY);
void TBigNum_Imprimir(TBigNum* Numero);

#endif
