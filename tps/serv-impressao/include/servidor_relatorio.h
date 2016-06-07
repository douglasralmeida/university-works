/*
**	TIPO ABSTRATO DE DADOS USUARIO
**	DOUGLAS RODRIGUES DE ALMEIDA
**
**	Relatorios do sistema
*/

#ifndef SERVIDOR_RELATORIO_H
#define SERVIDOR_RELATORIO_H

#include <stdio.h>	
#include <string.h>	
#include "boolutils.h"
#include "core.h"

/* Dados estatisticos do sistema */
typedef struct _TDados {
	int* Documentos;
	int* PaginasImpressas;
	int* Perdas;
	int* TempoMinimoEspera;
	int* TempoMaximoEspera;
	int* TempoTotalEspera;
	int TotalPrioridades;
} TDados;

typedef struct _TRelatorio {
	TDados* DadosPorTarefas;
	TDados* DadosPorUsuario;	
	int Documentos;
	int TempoMinimoEspera;
	int TempoMaximoEspera;
	int TempoTotalEspera;
	int TotalPaginasImpressas;
	int TotalPerdas;
	int TotalUsuariosInseridos;
	int TotalUsuariosRemovidos;
	int TotalTarefasRejeitadas;
} TRelatorio;
	

TDados* TDados_Criar(const int TotalPrioridades);

void TDados_Destruir(TDados** PDados);

void TDados_Emitir(TDados* Dados, FILE* Arquivo);

TRelatorio* TRelatorio_Criar(const int TotalPrioridades);

void TRelatorio_Destruir(TRelatorio** PRelatorio);

void TRelatorio_Emitir(TRelatorio* Relatorio, FILE* Arquivo);
#endif
