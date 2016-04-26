#include <stdio.h>
#include "relatorio.h"

void ExibirMedias(FILE* Arquivo, TCliente* ListaClientes, int Quantidade)
{
	int i;
	int total_atendidos = 0;
	int total_desistent = 0;
	int total_filageral = 0;
	int total_filadesis = 0;
	int total_tempoaten = 0;
	float valor_vendido = 0.0;
	float valor_perdido = 0.0;
	
	for (i = 0; i < Quantidade; i++)
	{
		if (ListaClientes[i].Desistencia)
		{
			total_desistent++;
			total_filadesis += ClienteMinutosTotal(ListaClientes + i);
			valor_perdido += ListaClientes[i].Gasto;
		}
		else
		{
			total_atendidos++;
			total_tempoaten += ClienteMinutosAtendimento(ListaClientes + i);
			total_filageral += ClienteMinutosEspera(ListaClientes + i);
			valor_vendido += ListaClientes[i].Gasto;
		}
	}
	total_filageral += total_filadesis;
	
	fprintf(Arquivo, "Tempo medio em fila geral: ");
	if (Quantidade > 0)
		GravarHora(Arquivo, MinutosParaHora(total_filageral / Quantidade));
	else
		fprintf(Arquivo, "00:00");
	fprintf(Arquivo, "\nTempo medio em fila antes de desistir: ");
	if (total_desistent > 0)
		GravarHora(Arquivo, MinutosParaHora(total_filadesis / total_desistent));
	else
		fprintf(Arquivo, "00:00");			
	fprintf(Arquivo, "\nTempo medio de atendimento: ");
	if (total_atendidos > 0)
		GravarHora(Arquivo, MinutosParaHora(total_tempoaten / total_atendidos));
	else
		fprintf(Arquivo, "00:00");
	fprintf(Arquivo, "\nValor vendido estimado: %.2f\n", valor_vendido);
	fprintf(Arquivo, "Valor perdido estimado: %.2f\n", valor_perdido);
}

void ExibirRelatorio(TAtendimento* Atendimento)
{
	fprintf(Atendimento->ArquivoRelatorio, "Consulta numero: %d\n", Atendimento->Relatorios + 1);
	Atendimento->Relatorios++;
	fprintf(Atendimento->ArquivoRelatorio, "Quantidade de clientes que entraram: %d\n", Atendimento->Quantidade);
	fprintf(Atendimento->ArquivoRelatorio, "Quantidade de clientes atendidos: %d\n", Atendimento->Atendidos);
	fprintf(Atendimento->ArquivoRelatorio, "Quantidade de clientes desistentes: %d\n", Atendimento->Quantidade - Atendimento->Atendidos);
	ExibirMedias(Atendimento->ArquivoRelatorio, Atendimento->ListaClientes, Atendimento->Quantidade);
}

void GravarHora(FILE*Arquivo, THora Hora)
{
	fprintf(Arquivo, "%02d:%02d", Hora / 60, Hora % 60);
}
