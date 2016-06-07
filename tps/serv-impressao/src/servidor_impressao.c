#include "servidor_impressao.h"

TImpressao* TImpressao_Criar(TUsuario* Usuario, time_t Horario, unsigned int MaxEspera, unsigned int Paginas, size_t Prioridade)
{
	TImpressao* NovaImpressao;
	
	NovaImpressao = (TUsuario*)malloc(sizeof(TUsuario));
	NovaImpressao->Usuario = Usuario;
	NovaImpressao->Horario = Horario;
	NovaImpressao->MaxExpera = MaxEspera;
	NovaImpressao->Paginas = Paginas;
	NovaImpressao->Prioridade = Prioridade;
	
	return NovaImpressao;
}

void TImpressao_Destruir(void** PImpressao)
{
	free(*PImpressao);
	PImpressao = NULL;
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
	strcopy(NovaImpressora->Nome, Nome);
	switch (Escalonador)
		case 1:
			FuncImpComparar = NULL;
		break;
		case 2:
			FuncImpComparar = &TImpressao_Comparar1;
		break;
		case 3:
			FuncImpComparar = &TImpressao_Comparar2;
		break;
		
	NovaImpressora->FilaImpressao = TFilaPrioridade_Criar(1024, FuncImpComparar, FuncImpDestruir);
	
	return NovaImpressora;
}

void TImpressora_Destruir(TImpressora** PImpressora)
{
	TFilaPrioridade_Destruir(&(*PImpressora)->FilaImpressao);
	free(*PUsuario);
	PUsuario = NULL;	
}

bool TImpressao_Comparar1(void* Impressao1, void* Impressao2)
{
	time_t horaatual;
	unsigned int tre1;
	unsigned int tre2;
	TImpressao* Imp1;
	TImpressao* Imp2;
	
	Imp1 = (TImpressao*)Impressao1;
	Imp2 = (TImpressao*)Impressao2;
	if (Imp1->Usuario->Prioridade == Imp2->Usuario->Prioridade)
	{
		horaatual = time(&horaatual);
		tre1 = Imp1->Horario + Imp1->MaxEspera - horaatual;
		tre2 = Imp2->Horario + Imp2->MaxEspera - horaatual;
		if (tre1 == tre2)
		{
			if (Imp1->Prioridade == Imp2->Prioridade)
			{
				return (Imp1->Horario < Imp1->Horario);
			}
			else
				return (Imp1->Prioridade < Imp2->Prioridade);
		}
		else(Imp1->Usuario->Prioridade == 0) && (Imp2->Usuario->Prioridade > 0)
			return (tre1 < tre2);
	}
	else
		return (Imp1->Usuario->Prioridade < Imp2->Usuario->Prioridade);	
}

bool TImpressao_Comparar2(void* Impressao1, void* Impressao2)
{
	time_t horaatual;
	unsigned int nivelprior1;
	unsigned int nivelprior2;
	unsigned int tempoespera1;
	unsigned int tempoespera2;
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
		{
			return (Imp1->MaxExpera < Imp2->MaxEspera);
		}
		else
			return (Imp1->Prioridade < Imp2->Prioridade);
	}
	else
	{
		horaatual = time(&horaatual);
		tempoespera1 = horaatual - Imp1->Horario;
		tempoespera2 = horaatual - Imp1->Horario;
		nivelprior1 = Impressao1->Usuario->Prioridade * 0.2 + Impressao1->Prioridade * 0.6 = Impressao1->MaxEspera / tempoespera1 * 0.2;
		nivelprior2 = Impressao2->Usuario->Prioridade * 0.2 + Impressao2->Prioridade * 0.6 = Impressao2->MaxEspera / tempoespera2 * 0.2;
		return (nivelprior1 < nivelprior2);
	}
}

void TImpressora_Imprimir(void)
{
	
}