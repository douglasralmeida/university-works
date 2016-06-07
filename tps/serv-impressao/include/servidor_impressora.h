/*
**	TIPO ABSTRATO DE DADOS USUARIO
**	DOUGLAS RODRIGUES DE ALMEIDA
**
**	Cadastro dos usuarios do sistemas
*/

#ifndef IMPRESSORA_H
#define IMPRESSORA_H

#include <string.h>
#include <time.h>
#include "boolutils.h"
#include "core.h"
#include "fila.h"
#include "filaprior.h"
#include "servidor_usuario.h"

typedef struct _TImpressao {
	time_t HorarioChegada;
	time_t HorarioLimite;
	unsigned int MaxEspera;
	unsigned int Paginas;
	size_t Prioridade;
	TUsuario* Usuario;
} TImpressao;

/* Impressora do sistema */
typedef struct _TImpressora {
	char Nome[11];
	size_t Capacidade;
	size_t Escalonador;
	time_t InicioTrabalhos;
	TFilaPrioridade* FilaImpressao;
	size_t TotalPrioridades;
} TImpressora;

TImpressao* TImpressao_Criar(TUsuario* Usuario, time_t Horario, unsigned int MaxEspera, unsigned int Paginas, size_t Prioridade);

void TImpressao_Destruir(void** PImpressao);

bool TImpressao_Comparar1(void* Impressao1, void* Impressao2);

bool TImpressao_Comparar2(void* Impressao1, void* Impressao2);

TImpressora* TImpressora_Criar(size_t Capacidade, size_t Escalonador, char* Nome);

void TImpressora_Destruir(TImpressora** PImpressora);

void TImpressora_Imprimir(TImpressora* Impressora, TUsuario* Usuario, const time_t Hora, const int Prioridade, const int Paginas, const int TempoMaximo);

#endif
