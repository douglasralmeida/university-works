#ifndef _FISICA_H_
#define _FISICA_H_

#include "tipos.h"
#include "matematica.h"

typedef enum {mvManual, mvReta} TMovimentoTipo;

void PosicaoMovimentar(TPonto* Ponto, TVetor* Velocidade);

#endif