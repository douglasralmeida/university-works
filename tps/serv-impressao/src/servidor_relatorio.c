/*
**	SERVIDOR DE IMPRESSSAO
**	DOUGLAS RODRIGUES DE ALMEIDA
**
**	Implementacao de TAD auxiliar para geracao de relatorios estatisticos
*/


#include <stdlib.h>
#include "servidor_relatorio.h"

void ZerarArray(int* Array, int n)
{
	int i;
	
	for (i = 0; i < n; i++)
		Array[i] = 0;
}

TDados* TDados_Criar(const int TotalPrioridades)
{
	TDados* NovoDados;
	
	NovoDados = (TDados*)malloc(sizeof(TDados));
	if (NovoDados == NULL)
	{
		printf("Erro. Erro ao alocar memoria.\n");
		return NULL;
	}
	NovoDados->Documentos = (int*)malloc(TotalPrioridades * sizeof(int));
	NovoDados->PaginasImpressas = (int*)malloc(TotalPrioridades * sizeof(int));
	NovoDados->Perdas = (int*)malloc(TotalPrioridades * sizeof(int));
	NovoDados->TempoMinimoEspera = (int*)malloc(TotalPrioridades * sizeof(int));
	NovoDados->TempoMaximoEspera = (int*)malloc(TotalPrioridades * sizeof(int));
	NovoDados->TempoTotalEspera = (int*)malloc(TotalPrioridades * sizeof(int));
	NovoDados->TotalPrioridades = TotalPrioridades;
	ZerarArray(NovoDados->Documentos, TotalPrioridades);
	ZerarArray(NovoDados->PaginasImpressas, TotalPrioridades);
	ZerarArray(NovoDados->Perdas, TotalPrioridades);
	ZerarArray(NovoDados->TempoMinimoEspera, TotalPrioridades);
	ZerarArray(NovoDados->TempoMaximoEspera, TotalPrioridades);
	ZerarArray(NovoDados->TempoTotalEspera, TotalPrioridades);					
	
	return NovoDados;
}

void TDados_Destruir(TDados** PDados)
{
	free((*PDados)->Documentos);
	free((*PDados)->PaginasImpressas);
	free((*PDados)->Perdas);
	free((*PDados)->TempoMinimoEspera);
	free((*PDados)->TempoMaximoEspera);
	free((*PDados)->TempoTotalEspera);	
	free(*PDados);
	PDados = NULL;
}

void TDados_Emitir(TDados* Dados, FILE* Arquivo)
{
	int i;
	float f;
		
	fprintf(Arquivo, "# total perdas:\n");
	for (i = 0; i < Dados->TotalPrioridades; i++)
		fprintf(Arquivo, "%d %d\n", i, Dados->Perdas[i]);
	fprintf(Arquivo, "# tempo medio espera:\n");
	for (i = 0; i < Dados->TotalPrioridades; i++)
	{
		if (Dados->Documentos[i] > 0)
			f = Dados->TempoTotalEspera[i] / Dados->Documentos[i];
		else
			f = 0.0;
		fprintf(Arquivo, "%d %.3f\n", i, f);
	}
	fprintf(Arquivo, "# tempo minimo espera:\n");
	for (i = 0; i < Dados->TotalPrioridades; i++)
		fprintf(Arquivo, "%d %d\n", i, Dados->TempoMinimoEspera[i]);
	fprintf(Arquivo, "# tempo maximo espera:\n");
	for (i = 0; i < Dados->TotalPrioridades; i++)
		fprintf(Arquivo, "%d %d\n", i, Dados->TempoMaximoEspera[i]);
	fprintf(Arquivo, "# numero de paginas impressas:\n");
	for (i = 0; i < Dados->TotalPrioridades; i++)
		fprintf(Arquivo, "%d %d\n", i, Dados->PaginasImpressas[i]);
}

TRelatorio* TRelatorio_Criar(const int TotalPrioridades)
{
	TRelatorio* NovoRelatorio;
	
	NovoRelatorio = (TRelatorio*)malloc(sizeof(TRelatorio));
	if (NovoRelatorio == NULL)
	{
		printf("Erro. Erro ao alocar memoria.\n");
		return NULL;
	}
	NovoRelatorio->DadosPorTarefas = TDados_Criar(TotalPrioridades);
	NovoRelatorio->DadosPorUsuario = TDados_Criar(TotalPrioridades);
	NovoRelatorio->Documentos = 0;
	NovoRelatorio->TempoMinimoEspera = 0;
	NovoRelatorio->TempoMaximoEspera = 0;
	NovoRelatorio->TempoTotalEspera = 0;
	NovoRelatorio->TotalPaginasImpressas = 0;
	NovoRelatorio->TotalPerdas = 0;
	NovoRelatorio->TotalUsuariosInseridos = 0;
	NovoRelatorio->TotalUsuariosRemovidos = 0;
	NovoRelatorio->TotalTarefasRejeitadas = 0;
	
	return NovoRelatorio;
}

void TRelatorio_Destruir(TRelatorio** PRelatorio)
{
	TDados_Destruir(&(*PRelatorio)->DadosPorTarefas);
	TDados_Destruir(&(*PRelatorio)->DadosPorUsuario);	
	free(*PRelatorio);
	PRelatorio = NULL;	
}

void TRelatorio_Emitir(TRelatorio* Relatorio, FILE* Arquivo)
{
	float f;
	
	fprintf(Arquivo, "## por prioridade de usuario\n");
	TDados_Emitir(Relatorio->DadosPorUsuario, Arquivo);
	fprintf(Arquivo, "## por prioridade de tarefa\n");
	TDados_Emitir(Relatorio->DadosPorTarefas, Arquivo);
	fprintf(Arquivo, "## geral:\n");
	fprintf(Arquivo, "# total perdas: %d\n", Relatorio->TotalPerdas);
	if (Relatorio->Documentos > 0)
		f = (float)Relatorio->TempoTotalEspera / Relatorio->Documentos;
	else
		f = 0.0;
	fprintf(Arquivo, "# tempo medio espera: %.3f\n", f);
	fprintf(Arquivo, "# tempo minimo espera: %d\n", Relatorio->TempoMinimoEspera);
	fprintf(Arquivo, "# tempo maximo espera: %d\n", Relatorio->TempoMaximoEspera);
	fprintf(Arquivo, "# numero de paginas impressas: %d\n", Relatorio->TotalPaginasImpressas);
	fprintf(Arquivo, "# quantidade de usuarios inseridos: %d\n", Relatorio->TotalUsuariosInseridos);
	fprintf(Arquivo, "# quantidade de usuarios removidos: %d\n", Relatorio->TotalUsuariosRemovidos);
	fprintf(Arquivo, "# quantidade de tarefas removidas com os usuarios: %d\n", Relatorio->TotalTarefasRejeitadas);
	
}
