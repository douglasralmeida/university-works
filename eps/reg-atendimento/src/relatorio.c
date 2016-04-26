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
	
	printf("Tempo medio em fila geral: ");
	if (Quantidade > 0)
		ImprimirHora(MinutosParaHora(total_filageral / Quantidade));
	else
		printf("00:00");
	printf("\nTempo medio em fila antes de desistir: ");
	if (total_desistent > 0)
		ImprimirHora(MinutosParaHora(total_filadesis / total_desistent));
	else
		printf("00:00");			
	printf("\nTempo medio de atendimento: ");
	if (total_atendidos > 0)
		ImprimirHora(MinutosParaHora(total_tempoaten / total_atendidos));
	else
		printf("00:00");
	printf("\nValor vendido estimado: %.2f\n", valor_vendido);
	printf("Valor perdido estimado: %.2f\n", valor_perdido);
}

void ExibirRelatorio(TAtendimento* Atendimento)
{
	printf("Consulta numero: %d\n", Atendimento->Relatorios + 1);
	Atendimento->Relatorios++;
	printf("Quantidade de clientes que entraram: %d\n", Atendimento->Quantidade);
	printf("Quantidade de clientes atendidos: %d\n", Atendimento->Atendidos);
	printf("Quantidade de clientes desistentes: %d\n", Atendimento->Quantidade - Atendimento->Atendidos);
	ExibirMedias(Atendimento->ListaClientes, Atendimento->Quantidade);
}
