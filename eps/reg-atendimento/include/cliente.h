#ifndef CLIENTE_H
#define CLIENTE_H

#include "datautils.h"

typedef struct TCliente_ {
	unsigned int Numero;
	float Gasto;
	THora Chegada;
	THora AtendimentoInicio;
	THora Saida;
	int Desistencia;
} TCliente;

#endif
