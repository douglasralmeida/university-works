#ifndef CLIENTE_H
#define CLIENTE_H

#include "datautils.h"

typedef struct TCliente_ {
	float Gasto;
	THora Chegada;
	THora AtendimentoInicio;
	THora Saida;
	int Desistencia;
	int Vazio;
} TCliente;

#endif
