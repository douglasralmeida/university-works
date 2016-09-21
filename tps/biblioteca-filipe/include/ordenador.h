/*
**	BIBLIOTECA DO FILIPE
**	DOUGLAS RODRIGUES DE ALMEIDA
**
**	Estrutura de dados do ordenador externo
*/

#ifndef ORDENADOR_H
#define ORDENADOR_H

#include "core.h"
#include "memoria.h"
#include "arquivo.h"

typedef struct _TOrdenador {
	TArquivo* ArquivoDados;
	TFuncaoComparar FuncaoComparar;
	size_t MaxItensPorVez;
} TOrdenador;

TOrdenador* TOrdenador_Criar(TArquivo* Dados, TFuncaoComparar FuncaoComparar, size_t MaxItensPorVez);

void TOrdenador_Destruir(TOrdenador** POrdenador);

void TOrdenador_Ordenar(TOrdenador* Ordenador);
#endif
