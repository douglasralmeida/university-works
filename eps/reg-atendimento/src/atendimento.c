#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "atendimento.h"

int BufferAnalisar(TAtendimento* Atendimento, char* Buffer, int Tamanho)
{
	int Comando = 0;
	char* linha_inicio;
	char* p;
	char* temp;

	p = Buffer;
	while (*p != '\0')
	{
		/* primeiro item da linha: comando */
		Comando = strtol(p, &temp, 10);
		linha_inicio = p;
		switch (Comando)
		{
			case	CMD_NOVOCLIENTE:
				/* sscanf(p, "%s %s %s");*/
			break;
			case	CMD_ATENDINICIO:
			case	CMD_ATENDCONCLU:
			case	CMD_DESISTENCIA:
				/* sscanf(p, "%s %s");*/
			break;
			case	CMD_EXRELATORIO:
				/* print */
			break;
			case	CMD_SISTEMASAIR:
				
			break;
		}
		/* caminha ate o final da linha */
		p = (char*) memchr(p, '\n', (Buffer + Tamanho) - p);
		p++;
	}
}

int EntradaLerCabecalho(char* Buffer)
{
	int Resultado;
	
	sscanf(Buffer, "%d", &Resultado);
	
	return Resultado;
}

void EntradaAnalisar(int Descritor)
{
	size_t BytesLidos;
	char Buffer[BUFFER_TAMANHO + 1];
	int LeuCabecalho = 0;
	int ArquivoChegouAoFim = 0;
	int QuantidadeClientes;
	TAtendimento* Atendimento;

	/* Avisa o kernel do nosso padrao de acesso.  */
	posix_fadvise(DescritorArquivo, 0, 0, 1); /*FDADVICE_SEQUENTIAL*/
	while (!ArquivoChegouAoFim)
	{
		/* gera buffers de 16kbytes do arquivo de entrada */
		BytesLidos = read(DescritorArquivo, Buffer, BUFFER_TAMANHO);
		Buffer[BUFFER_TAMANHO] = '\0';
		if (BytesLidos == (size_t) - 1)
		{
			printf("Erro ao acessar o arquivo de entrada.\n");
			ArquivoChegouAoFim = 1;
		}
		else if (!BytesLidos)
		{
			ArquivoChegouAoFim = 1;
		}
		else
		{
			/* ler cabecalho com quantidade de clientes */
			if (!LeuCabecalho)
			{
				QuantidadeClientes = LerCabecalho(Buffer);
				Buffer += 2;
				LeuCabecalho = 1;
				if (QuantidadeClientes > 0)
					Atendimento = AtendimentoCriar(QuantidadeClientes);
				else	
					break;
			}
			
			/* analisar o buffer */
			BufferAnalisar(Atendimento, Buffer, BUFFER_TAMANHO);
		}
	}
}

TAtendimento* AtendimentoCriar(int NovaCapacidade)
{
	TAtendimento* NovoAtendimento;
	
	NovoAtendimento = malloc(sizeof(TAtendimento));
	NovoAtendimento->Atendidos = 0;
	NovoAtendimento->Capacidade = NovaCapacidade;
	NovoAtendimento->ListaClientes = malloc(sizeof(TCliente) * NovaCapacidade);
	NovoAtendimento->Quantidade = 0;
	
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
	Atendimento->ListaClientes[ID]->Chegada = Chegada;
	Atendimento->ListaClientes[ID]->Vazio = 0;
	Atendimento->ListaClientes[ID]->Gasto = Valor;
	Atendimento->Quantidade++;
}

void AtendimentoClienteAtender(TAtendimento* Atendimento, unsigned int ID, THora Hora)
{
	Atendimento->ListaClientes[ID]->AtendimentoInicio = Hora;
}

void AtendimentoClienteConcluir(TAtendimento* Atendimento, unsigned int ID, THora Hora)
{
	Atendimento->ListaClientes[ID]->Saida = Hora;
	Atendimento->Atendidos++;
}

void AtendimentoClienteDesistencia(TAtendimento* Atendimento, unsigned int ID, THora Hora)
{
	Atendimento->ListaClientes[ID]->Saida = Hora;
	Atendimento->ListaClientes[ID]->Desistencia = 1;
}

void AtendimentoProcessarDados(char* Arquivo)
{
	int DescritorArquivo;

	DescritorArquivo = ArquivoAbrir(Arquivo);
	if (DescritorArquivo != -1)
	{
		AnalisarDados(DescritorArquivo);
		ArquivoFechar(DescritorArquivo);
	}
	else
	{
		printf("Erro ao abrir arquivo de entrada de dados.\n");
	}
}
