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

TAtendimento* AtendimentoCriar(int NovaCapacidade)
{
	int i;
	TAtendimento* NovoAtendimento;
	
	NovoAtendimento = malloc(sizeof(TAtendimento));
	NovoAtendimento->Atendidos = 0;
	NovoAtendimento->Capacidade = NovaCapacidade;
	NovoAtendimento->ListaClientes = malloc(sizeof(TCliente) * NovaCapacidade);
	NovoAtendimento->Quantidade = 0;
	NovoAtendimento->Relatorios = 0;
	for (i = 0; i < NovaCapacidade; i++)
		ClienteLimpar(NovoAtendimento->ListaClientes + i);
	
	return NovoAtendimento;
}

void AtendimentoDestruir(TAtendimento** PAtendimento)
{
	free((*PAtendimento)->ListaClientes);
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

void AtendimentoProcessarEntrada(const char* NomeArquivo)
{
	FILE* Arquivo;
	char Buffer[BUFFER_TAMANHO + 1];
	int Sair = 0;

	TAtendimento* Atendimento;
	int QuantidadeClientes;

	Arquivo = ArquivoAbrir(NomeArquivo);
	if (Arquivo != NULL)
	{		
		/* Ler cabecalho */
		if (fgets(Buffer, BUFFER_TAMANHO, Arquivo) != NULL)
		{
			QuantidadeClientes = BufferLerCabecalho(Buffer);			
		}
		if (QuantidadeClientes > 0)
		{
			Atendimento = AtendimentoCriar(QuantidadeClientes);
			if (Atendimento != NULL)
			{
				while ((Sair = 0) || (fgets(Buffer, BUFFER_TAMANHO, Arquivo) != NULL))
				{
					Sair = BufferAnalisar(Atendimento, Buffer);
				}
			}
		}
		AtendimentoDestruir(&Atendimento);
		ArquivoFechar(Arquivo);
	}
	else
	{
		printf("Erro ao abrir arquivo de entrada de dados.\n");
	}
}
