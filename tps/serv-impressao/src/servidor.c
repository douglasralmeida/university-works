/*
**	SERVIDOR 
**	DOUGLAS RODRIGUES DE ALMEIDA
**
**	Implementacao do servidor
*/

#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "servidor_arquivo.h"
#include "servidor_usuario.h"
#include "servidor.h"

TServidor* TServidor_Criar(void)
{
	TServidor* NovoServidor;
	TFuncaoDestruir FuncUsuarDestruir;
	TFuncaoIguais FuncUsuarIguais;
	
	FuncUsuarDestruir = &TUsuario_Destruir;
	FuncUsuarIguais = &TUsuario_Iguais;
	NovoServidor = (TServidor*)malloc(sizeof(TServidor));
	NovoServidor->Usuarios = TLista_Criar(FuncUsuarDestruir, FuncUsuarIguais, NULL);
	
	return NovoServidor;
}

void TServidor_Destruir(TServidor** PServidor)
{
	if ((*PServidor)->Impressora != NULL)
		free((*PServidor)->Impressora);
	TLista_Destruir(&(*PServidor)->Usuarios);
	free(*PServidor);
	PServidor = NULL;
}

bool TServidor_Analisar(TServidor* Servidor)
{
	char buffer[BUFFER_TAMANHO + 1];
	bool encerraanalise;
	
	encerraanalise = false;
	/* Ler primeira linha com cadastro da impressora */
	if ((fgets(buffer, BUFFER_TAMANHO, Servidor->ArquivoEntrada) != NULL) && (BufferImpressora(Servidor, buffer)))
			while ((encerraanalise == false) && (fgets(buffer, BUFFER_TAMANHO, Servidor->ArquivoEntrada) != NULL))
				encerraanalise = BufferAnalisar(Servidor, buffer);
		else	
		{
			printf("Erro (0x101): Erro ao abrir arquivo de entrada de dados.\n");
			return false;
		}
	return true;
}

bool TServidor_CadastrarImpressora(TServidor* Servidor, char* Impressora, int Capacidade, int Escalonador)
{
	Servidor->Impressora = TImpressora_Criar(Capacidade, Escalonador, Impressora);
	if (Servidor->Impressora == NULL)
		return false;
	
	return true;
}

void TServidor_Finalizar(TServidor* Servidor)
{
	fclose(Servidor->ArquivoEntrada);
	fclose(Servidor->ArquivoSaida);
}

void TServidor_Imprimir(TServidor* Servidor, const char* Nome, const time_t Hora, const int Prioridade, const int Paginas, const int TempoMaximo)
{
	TListaNo* No;
	TUsuario* Usuario;
	
	Usuario = TUsuario_Criar(Nome, 0);
	No = TLista_Pesquisar(Servidor->Usuarios, Usuario);
	if (No != NULL)
		TImpressora_Imprimir(Servidor->Impressora, (TUsuario*)No->Item, Hora, Prioridade, Paginas, TempoMaximo);
	free(Usuario);
}

bool TServidor_Preparar(TServidor* Servidor, const char* NomeArquivoEntrada, const char* NomeArquivoSaida)
{
	Servidor->ArquivoEntrada = fopen(NomeArquivoEntrada , "rt");
	Servidor->ArquivoSaida = fopen(NomeArquivoSaida , "wt");
	
	return ((Servidor->ArquivoEntrada != NULL) && (Servidor->ArquivoSaida != NULL));
}

void TServidor_Relatorio(TServidor* Servidor)
{
	int i;
	int totalprioridades = 1;
	float numero_f;
	int numero_i;
	
	fprintf(Servidor->ArquivoSaida, "## por prioridade de usuario\n");
	fprintf(Servidor->ArquivoSaida, "# total perdas:\n");
	for (i = 0; i < totalprioridades; i++)
	{
		numero_i = 0;
		fprintf(Servidor->ArquivoSaida, "%d %d\n", i, numero_i);
	}
	fprintf(Servidor->ArquivoSaida, "# tempo medio espera:\n");
	for (i = 0; i < totalprioridades; i++)
	{
		numero_f = 0.0;
		fprintf(Servidor->ArquivoSaida, "%d %.3f\n", i, numero_f);
	}
	fprintf(Servidor->ArquivoSaida, "# tempo minimo espera:\n");
	for (i = 0; i < totalprioridades; i++)
	{
		numero_i = 0;
		fprintf(Servidor->ArquivoSaida, "%d %d\n", i, numero_i);
	}
	fprintf(Servidor->ArquivoSaida, "# tempo maximo espera:\n");
	for (i = 0; i < totalprioridades; i++)
	{
		numero_i = 0;
		fprintf(Servidor->ArquivoSaida, "%d %d\n", i, numero_i);
	}
	fprintf(Servidor->ArquivoSaida, "# numero de paginas impressas:\n");
	for (i = 0; i < totalprioridades; i++)
	{
		numero_i = 0;
		fprintf(Servidor->ArquivoSaida, "%d %d\n", i, numero_i);
	}
	fprintf(Servidor->ArquivoSaida, "## por prioridade de tarefa\n");
	fprintf(Servidor->ArquivoSaida, "# total perdas:\n");
	for (i = 0; i < totalprioridades; i++)
	{
		numero_i = 0;
		fprintf(Servidor->ArquivoSaida, "%d %d\n", i, numero_i);
	}
	fprintf(Servidor->ArquivoSaida, "# tempo medio espera:\n");
	for (i = 0; i < totalprioridades; i++)
	{
		numero_f = 0.0;
		fprintf(Servidor->ArquivoSaida, "%d %.3f\n", i, numero_f);
	}
	fprintf(Servidor->ArquivoSaida, "# tempo minimo espera:\n");
	for (i = 0; i < totalprioridades; i++)
	{
		numero_i = 0;
		fprintf(Servidor->ArquivoSaida, "%d %d\n", i, numero_i);
	}
	fprintf(Servidor->ArquivoSaida, "# tempo maximo espera:\n");
	for (i = 0; i < totalprioridades; i++)
	{
		numero_i = 0;
		fprintf(Servidor->ArquivoSaida, "%d %d\n", i, numero_i);
	}
	fprintf(Servidor->ArquivoSaida, "# numero de paginas impressas:\n");
	for (i = 0; i < totalprioridades; i++)
	{
		numero_i = 0;
		fprintf(Servidor->ArquivoSaida, "%d %d\n", i, numero_i);
	}
	fprintf(Servidor->ArquivoSaida, "## geral:\n");
	numero_i = 0;
	fprintf(Servidor->ArquivoSaida, "# total perdas: %d\n", numero_i);
	numero_f = 0.0;
	fprintf(Servidor->ArquivoSaida, "# tempo medio espera: %.3f\n", numero_f);
	numero_i = 0;
	fprintf(Servidor->ArquivoSaida, "# tempo minimo espera: %d\n", numero_i);
	numero_i = 0;
	fprintf(Servidor->ArquivoSaida, "# tempo maximo espera: %d\n", numero_i);
	numero_i = 0;
	fprintf(Servidor->ArquivoSaida, "# numero de paginas impressas: %d\n", numero_i);
	numero_i = 0;
	fprintf(Servidor->ArquivoSaida, "# quantidade de usuarios inseridos: %d\n", numero_i);
	numero_i = 0;
	fprintf(Servidor->ArquivoSaida, "# quantidade de usuarios removidos: %d\n", numero_i);
	numero_i = 0;
	fprintf(Servidor->ArquivoSaida, "# quantidade de tarefas removidas com os usuarios: %d\n", numero_i);
}

void TServidor_UsuarioExcluir(TServidor* Servidor, const char* Nome)
{
	TListaNo* No;
	TUsuario* Usuario;
	
	Usuario = TUsuario_Criar(Nome, 0);
	No = TLista_Pesquisar(Servidor->Usuarios, Usuario);
	TLista_Remover(Servidor->Usuarios, No);
	TUsuario_Destruir((void**)&Usuario);
}

void TServidor_UsuarioNovo(TServidor* Servidor, const char* Nome, const int Prioridade)
{
	TUsuario* Usuario;
	
	Usuario = TUsuario_Criar(Nome, Prioridade);
	TLista_Adicionar(Servidor->Usuarios, Usuario);
}
