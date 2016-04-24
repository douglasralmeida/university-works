#include <stdio.h>
#include "relatorio.h"

void ExibirMedias(TCliente* ListaClientes, int Quantidade)
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
			total_filadesis += HoraParaMinutos(ListaClientes[i].Saida) - HoraParaMinutos(ListaClientes[i].Chegada);
			valor_perdido += ListaClientes[i].Gasto;
		}
		else
		{
			total_atendidos++;
			total_tempoaten += HoraParaMinutos(ListaClientes[i].Saida) - HoraParaMinutos(ListaClientes[i].AtendimentoInicio);
			total_filageral += HoraParaMinutos(ListaClientes[i].AtendimentoInicio) - HoraParaMinutos(ListaClientes[i].Chegada);
			valor_vendido += ListaClientes[i].Gasto;
		}
	}
	total_filageral += total_filadesis;
	
	printf("Tempo medio em fila geral: ");
	ImprimirHora(MinutosParaHora(total_filageral / Quantidade));
	printf("Tempo medio em fila antes de desistir: ");
	ImprimirHora(MinutosParaHora(total_filadesis / total_desistent));
	printf("\nTempo medio de atendimento: ");
	ImprimirHora(MinutosParaHora(total_tempoaten / total_atendidos));
	printf("Valor vendido estimado: %.2f\n", valor_vendido);
	printf("Valor perdido estimado: %.2f\n", valor_perdido);
}

void ExibirRelatorio(TAtendimento* Atendimento)
{
	printf("Consulta numero: %d\n", 1);
	printf("Quantidade de clientes que entraram: %d\n", Atendimento->Quantidade);
	printf("Quantidade de clientes atendidos: %d\n", Atendimento->Atendidos);
	printf("Quantidade de clientes desistentes: %d\n", Atendimento->Quantidade - Atendimento->Atendidos);
	ExibirMedias(Atendimento->ListaClientes, Atendimento->Quantidade);
}
