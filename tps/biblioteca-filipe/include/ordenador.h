/*
**	BIBLIOTECA DO FILIPE
**	DOUGLAS RODRIGUES DE ALMEIDA
**
**	Estrutura de dados do ordenador externo
*/

#ifndef ORDENADOR_H
#define ORDENADOR_H

#include <stdio.h>
#include "core.h"

typedef struct _TOrdenador {
	FILE* ArquivoLeEscreveSup;
	FILE* ArquivoLeInf;
	FILE* ArquivoEscreveInf;
	TFuncaoComparar FuncaoComparar;
	TFuncaoCopiar FuncaoCopiar;
	void* LimiteInferior;
	void* LimiteSuperior;
	size_t MaxItensPorVez;
	int Quantidade;
	void* Registro;
	size_t TamRegistro;
	int Variaveis[4];
} TOrdenador;

TOrdenador* TOrdenador_Criar(char* NomeArquivo, TFuncaoComparar FuncaoComparar, TFuncaoCopiar FuncaoCopiar, size_t MaxItensPorVez);

void TOrdenador_Destruir(TOrdenador** POrdenador);

void TOrdenador_Ordenar(TOrdenador* Ordenador);
#endif
