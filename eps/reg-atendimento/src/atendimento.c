#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arquivo.h"
#include "atendimento.h"
#include "relatorio.h"

int BufferAnalisar(TAtendimento* Atendimento, char* Buffer)
{
	int Comando = 0;
	int SairSistema = 0;
	
	char texto[6];
	int inteiro;
	float moeda;
	THora hora;

	/* primeiro item da linha: comando */
	Comando = Buffer[0] - '0';
	switch (Comando)
	{
		case	CMD_NOVOCLIENTE:
			sscanf(Buffer, "%*d %5s %d %f", texto, &inteiro, &moeda);
			hora = StringParaHora(texto);
			AtendimentoClienteAdicionar(Atendimento, inteiro, hora, moeda);
		break;
		case	CMD_ATENDINICIO:
			sscanf(Buffer, "%*d %5s %d", texto, &inteiro);
			hora = StringParaHora(texto);
			AtendimentoClienteAtender(Atendimento, inteiro, hora);
		break;
		case	CMD_ATENDCONCLU:
			sscanf(Buffer, "%*d %5s %d", texto, &inteiro);
			hora = StringParaHora(texto);
			AtendimentoClienteConcluir(Atendimento, inteiro, hora);
		break;
		case	CMD_DESISTENCIA:
			sscanf(Buffer, "%*d %5s %d", texto, &inteiro);
			hora = StringParaHora(texto);
			AtendimentoClienteDesistencia(Atendimento, inteiro, hora);
		break;
		case	CMD_EXRELATORIO:
			ExibirRelatorio(Atendimento);
		break;
		case	CMD_SISTEMASAIR:
			SairSistema = 1;
		break;
	}
	return SairSistema;
}

int BufferLerCabecalho(char* Buffer)
{
	int Resultado;
	
	sscanf(Buffer, "%d", &Resultado);
	
	return Resultado;
}

TAtendimento* AtendimentoCriar(int NovaCapacidade, const char* ArquivoRelatorio)
{
	int i;
	TAtendimento* NovoAtendimento;
	
	NovoAtendimento = malloc(sizeof(TAtendimento));
	if (!NovoAtendimento)
	{
		printf("Erro ao alocar memoria.\n");
		return NULL;	
	}
	NovoAtendimento->Atendidos = 0;
	NovoAtendimento->Capacidade = NovaCapacidade;
	NovoAtendimento->ListaClientes = malloc(sizeof(TCliente) * NovaCapacidade);
	if (!NovoAtendimento->ListaClientes)
	{
		printf("Erro ao alocar memoria.\n");
		free(NovoAtendimento);
		return NULL;
	}
	NovoAtendimento->Quantidade = 0;
	NovoAtendimento->Relatorios = 0;
	NovoAtendimento->ArquivoRelatorio = ArquivoAbrirEscrita(ArquivoRelatorio);
	if (NovoAtendimento->ArquivoRelatorio != NULL)
	{
		for (i = 0; i < NovaCapacidade; i++)
			ClienteLimpar(NovoAtendimento->ListaClientes + i);	
		return NovoAtendimento;
	}
	else
	{
		printf("Erro ao abrir arquivo de saida de dados.\n");
		free(NovoAtendimento->ListaClientes);
		free(NovoAtendimento);
		return NULL;
	}
}

void AtendimentoDestruir(TAtendimento** PAtendimento)
{
	if ((*PAtendimento)->ListaClientes != NULL)
		free((*PAtendimento)->ListaClientes);
	if ((*PAtendimento)->ArquivoRelatorio != NULL)
		ArquivoFechar((*PAtendimento)->ArquivoRelatorio);		
	free(*PAtendimento);
	*PAtendimento = NULL;
}

void AtendimentoClienteAdicionar(TAtendimento* Atendimento, unsigned int ID, THora Chegada, float Valor)
{
	Atendimento->ListaClientes[ID-1].Chegada = Chegada;
	Atendimento->ListaClientes[ID-1].Vazio = 0;
	Atendimento->ListaClientes[ID-1].Gasto = Valor;
	Atendimento->Quantidade++;
}

void AtendimentoClienteAtender(TAtendimento* Atendimento, unsigned int ID, THora Hora)
{
	Atendimento->ListaClientes[ID-1].AtendimentoInicio = Hora;
}

void AtendimentoClienteConcluir(TAtendimento* Atendimento, unsigned int ID, THora Hora)
{
	Atendimento->ListaClientes[ID-1].Saida = Hora;
	Atendimento->Atendidos++;
}

void AtendimentoClienteDesistencia(TAtendimento* Atendimento, unsigned int ID, THora Hora)
{
	Atendimento->ListaClientes[ID-1].Saida = Hora;
	Atendimento->ListaClientes[ID-1].Desistencia = 1;
}

void AtendimentoProcessarEntrada(const char* NomeArquivoEntrada, const char* NomeArquivoSaida)
{
	FILE* ArquivoEntrada;
	char Buffer[BUFFER_TAMANHO + 1];
	int Sair = 0;

	TAtendimento* Atendimento;
	int QuantidadeClientes;

	ArquivoEntrada = ArquivoAbrirLeitura(NomeArquivoEntrada);
	if (ArquivoEntrada != NULL)
	{		
		/* Ler cabecalho */
		if (fgets(Buffer, BUFFER_TAMANHO, ArquivoEntrada) != NULL)
		{
			QuantidadeClientes = BufferLerCabecalho(Buffer);			
		}
		if (QuantidadeClientes > 0)
		{
			Atendimento = AtendimentoCriar(QuantidadeClientes, NomeArquivoSaida);
			if (Atendimento != NULL)
			{
				while ((Sair = 0) || (fgets(Buffer, BUFFER_TAMANHO, ArquivoEntrada) != NULL))
				{
					Sair = BufferAnalisar(Atendimento, Buffer);
				}
			}
		}
		AtendimentoDestruir(&Atendimento);
		ArquivoFechar(ArquivoEntrada);
	}
	else
	{
		printf("Erro ao abrir arquivo de entrada de dados.\n");
	}
}
