/*
 *	TIPO ABASTRATO DE DADOS FILA
 *	DOUGLAS RODRIGUES DE ALMEIDA
 *
 *	Cabecalho e estruturas de uma fila
 *	
 */

#ifndef FILA_H
#define FILA_H

#include <stdio.h>
#include <stdlib.h>
#include "boolutils.h"
#include "item.h"

/* Estrutura do no da fila */
typedef struct _TFilaNo TFilaNo;

struct _TFilaNo {
	TFilaItem Item;
	TFilaNo* Proximo;
};

/* Estrutura da fila simples */
typedef struct _TFila {
	unsigned int Tamanho;
	TFilaNo* Frente;
	TFilaNo* Tras;
} TFila;

TFila* TFila_Criar();

void TFila_Destruir();

void TFila_Enfileirar(TFila Item);

TFilaItem TFila_Desenfileirar();
