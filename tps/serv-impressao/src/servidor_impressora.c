#include <stdlib.h>
#include <string.h>
#include "hora.h"
#include <time.h>
#include "list.h"
#include "servidor.h"
#include "servidor_impressora.h"

TImpressao* TImpressao_Criar(TUsuario* Usuario, time_t Horario, unsigned int MaxEspera, unsigned int Paginas, size_t Prioridade)
{
	TImpressao* NovaImpressao;
	
	NovaImpressao = (TImpressao*)malloc(sizeof(TImpressao));
	NovaImpressao->Usuario = Usuario;
	NovaImpressao->HorarioChegada = Horario;
	NovaImpressao->HorarioLimite = Horario + MaxEspera;
	NovaImpressao->MaxEspera = MaxEspera;
	NovaImpressao->Paginas = Paginas;
	NovaImpressao->Prioridade = Prioridade;	
	
	return NovaImpressao;
}

void TImpressao_Destruir(void** PImpressao)
{
	TUsuario_Destruir((void**)&((TImpressao*)*PImpressao)->Usuario);
	free(*PImpressao);
	PImpressao = NULL;
}

bool TImpressao_Comparar1(void* Impressao1, void* Impressao2)
{
	time_t tre1;
	time_t tre2;
	TImpressao* Imp1;
	TImpressao* Imp2;
	
	Imp1 = (TImpressao*)Impressao1;
	Imp2 = (TImpressao*)Impressao2;
	if (Imp1->Usuario->Prioridade == Imp2->Usuario->Prioridade)
	{
		tre1 = Imp1->HorarioLimite - horaatual;
		tre2 = Imp2->HorarioLimite - horaatual;
		if (tre1 == tre2)
		{
			if (Imp1->Prioridade == Imp2->Prioridade)
			{
				return (Imp1->HorarioChegada < Imp1->HorarioChegada);
			}
			else
				return (Imp1->Prioridade < Imp2->Prioridade);
		} 
		else
			return (tre1 < tre2);
	}
	else
		return (Imp1->Usuario->Prioridade < Imp2->Usuario->Prioridade);	
}

bool TImpressao_Comparar2(void* Impressao1, void* Impressao2)
{
	float nivelprior1;
	float nivelprior2;
	unsigned int tespera1;
	unsigned int tespera2;
	TImpressao* Imp1;
	TImpressao* Imp2;
	
	Imp1 = (TImpressao*)Impressao1;
	Imp2 = (TImpressao*)Impressao2;
	
	if ((Imp1->Usuario->Prioridade == 0) && (Imp2->Usuario->Prioridade > 0))
	{
		return true;
	}
	else if ((Imp1->Usuario->Prioridade == 0) && (Imp2->Usuario->Prioridade == 0))
	{
		if (Imp1->Prioridade == Imp2->Prioridade)
			return (Imp1->MaxEspera < Imp2->MaxEspera);
		else
			return (Imp1->Prioridade < Imp2->Prioridade);
	}
	else
	{
		tespera1 = horaatual - Imp1->HorarioChegada;
		tespera2 = horaatual - Imp2->HorarioChegada;
		if (Imp1->MaxEspera > 0)
			nivelprior1 = Imp1->Usuario->Prioridade * 0.2 + Imp1->Prioridade * 0.6 + tespera1 / Imp1->MaxEspera * 0.2;
		else
			nivelprior1 = Imp1->Usuario->Prioridade * 0.2 + Imp1->Prioridade * 0.6;
		if (Imp2->MaxEspera > 0)
			nivelprior2 = Imp2->Usuario->Prioridade * 0.2 + Imp2->Prioridade * 0.6 + tespera2 / Imp2->MaxEspera * 0.2;
		else
			nivelprior2 = Imp2->Usuario->Prioridade * 0.2 + Imp2->Prioridade * 0.6;
		return (nivelprior1 < nivelprior2); 
	}
}

bool TImpressao_Comparar3(void* Impressao1, void* Impressao2)
{
	TImpressao* Imp1;
	TImpressao* Imp2;
	
	Imp1 = (TImpressao*)Impressao1;
	Imp2 = (TImpressao*)Impressao2;

	return (Imp1->HorarioChegada < Imp2->HorarioChegada);	
}

TImpressora* TImpressora_Criar(size_t Capacidade, size_t Escalonador, char* Nome)
{
	TImpressora* NovaImpressora;
	TFuncaoComparar FuncImpComparar;
	TFuncaoDestruir FuncImpDestruir;
	
	FuncImpDestruir = &TImpressao_Destruir;
	NovaImpressora = (TImpressora*)malloc(sizeof(TImpressora));
	NovaImpressora->Capacidade = Capacidade;
	NovaImpressora->Escalonador = Escalonador;
	strcpy(NovaImpressora->Nome, Nome);
	switch (Escalonador)
	{
		case 1:
			FuncImpComparar = &TImpressao_Comparar3;
		break;
		case 2:
			FuncImpComparar = &TImpressao_Comparar1;
		break;
		case 3:
			FuncImpComparar = &TImpressao_Comparar2;
		break;
	}	
	NovaImpressora->FilaImpressao = TFilaPrioridade_Criar(1024, FuncImpComparar, FuncImpDestruir);
	if (NovaImpressora->FilaImpressao == NULL)
	{
		free(NovaImpressora);
		return NULL;
	}
	NovaImpressora->ImpressaoRecebida = NULL;
	NovaImpressora->TotalPrioridades = QUANT_PRIORIDADES;
	
	return NovaImpressora;
}

void TImpressora_Destruir(TImpressora** PImpressora)
{
	TFilaPrioridade_Destruir(&(*PImpressora)->FilaImpressao);
	free(*PImpressora);
	PImpressora = NULL;	
}

void TImpressora_Cancelar(TImpressao* Impressao, TRelatorio* Relatorio)
{
	time_t tempoespera;
	
	tempoespera = horaatual - Impressao->HorarioChegada;
	Relatorio->DadosPorTarefas->Documentos[Impressao->Prioridade]++;
	if (tempoespera < Relatorio->DadosPorTarefas->TempoMinimoEspera[Impressao->Prioridade])
		Relatorio->DadosPorTarefas->TempoMinimoEspera[Impressao->Prioridade] = tempoespera;
	if (tempoespera > Relatorio->DadosPorTarefas->TempoMaximoEspera[Impressao->Prioridade])
		Relatorio->DadosPorTarefas->TempoMaximoEspera[Impressao->Prioridade] = tempoespera;
	Relatorio->DadosPorUsuario->Documentos[Impressao->Usuario->Prioridade]++;
	if (tempoespera < Relatorio->DadosPorUsuario->TempoMinimoEspera[Impressao->Usuario->Prioridade])
		Relatorio->DadosPorUsuario->TempoMinimoEspera[Impressao->Usuario->Prioridade] = tempoespera;
	else if (tempoespera > Relatorio->DadosPorUsuario->TempoMaximoEspera[Impressao->Usuario->Prioridade])
		Relatorio->DadosPorUsuario->TempoMaximoEspera[Impressao->Usuario->Prioridade] = tempoespera;	
	Relatorio->DadosPorTarefas->TempoTotalEspera[Impressao->Prioridade] += tempoespera;
	Relatorio->DadosPorUsuario->TempoTotalEspera[Impressao->Usuario->Prioridade] += tempoespera;
	Relatorio->DadosPorTarefas->Perdas[Impressao->Prioridade]++;
	Relatorio->DadosPorUsuario->Perdas[Impressao->Usuario->Prioridade]++;
	Relatorio->Documentos++;	
	if (tempoespera < Relatorio->TempoMinimoEspera)
		Relatorio->TempoMinimoEspera = tempoespera;
	if (tempoespera > Relatorio->TempoMaximoEspera)
		Relatorio->TempoMaximoEspera = tempoespera;
	Relatorio->TempoTotalEspera = Relatorio->TempoTotalEspera + tempoespera;
	Relatorio->TotalPerdas++;
	
	TImpressao_Destruir((void**)&Impressao);	
}

void TImpressora_Imprimir(TImpressao* Impressao, TRelatorio* Relatorio)
{
	time_t tempoespera;
	
	tempoespera = horaatual - Impressao->HorarioChegada;
	Relatorio->DadosPorTarefas->Documentos[Impressao->Prioridade]++;
	Relatorio->DadosPorTarefas->PaginasImpressas[Impressao->Prioridade] += Impressao->Paginas;
	if (tempoespera < Relatorio->DadosPorTarefas->TempoMinimoEspera[Impressao->Prioridade])
		Relatorio->DadosPorTarefas->TempoMinimoEspera[Impressao->Prioridade] = tempoespera;
	if (tempoespera > Relatorio->DadosPorTarefas->TempoMaximoEspera[Impressao->Prioridade])
		Relatorio->DadosPorTarefas->TempoMaximoEspera[Impressao->Prioridade] = tempoespera;
	Relatorio->DadosPorUsuario->Documentos[Impressao->Usuario->Prioridade]++;
	Relatorio->DadosPorUsuario->PaginasImpressas[Impressao->Usuario->Prioridade] += Impressao->Paginas;
	if (tempoespera < Relatorio->DadosPorUsuario->TempoMinimoEspera[Impressao->Usuario->Prioridade])
		Relatorio->DadosPorUsuario->TempoMinimoEspera[Impressao->Usuario->Prioridade] = tempoespera;
	else if (tempoespera > Relatorio->DadosPorUsuario->TempoMaximoEspera[Impressao->Usuario->Prioridade])
		Relatorio->DadosPorUsuario->TempoMaximoEspera[Impressao->Usuario->Prioridade] = tempoespera;	
	Relatorio->DadosPorTarefas->TempoTotalEspera[Impressao->Prioridade] += tempoespera;
	Relatorio->DadosPorUsuario->TempoTotalEspera[Impressao->Usuario->Prioridade] += tempoespera;
	Relatorio->Documentos++;
	if (tempoespera < Relatorio->TempoMinimoEspera)
		Relatorio->TempoMinimoEspera = tempoespera;
	if (tempoespera > Relatorio->TempoMaximoEspera)
		Relatorio->TempoMaximoEspera = tempoespera;
	Relatorio->TempoTotalEspera = Relatorio->TempoTotalEspera + tempoespera;
	Relatorio->TotalPaginasImpressas += Impressao->Paginas;
	TImpressao_Destruir((void**)&Impressao);
}
