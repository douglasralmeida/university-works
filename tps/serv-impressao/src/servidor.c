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
#include "servidor_relatorio.h"
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
	NovoServidor->Impressora = NULL;
	NovoServidor->Relatorio = NULL;
	NovoServidor->Usuarios = TLista_Criar(FuncUsuarDestruir, FuncUsuarIguais, NULL);
	
	return NovoServidor;
}

void TServidor_Destruir(TServidor** PServidor)
{
	if ((*PServidor)->Impressora != NULL)
		TImpressora_Destruir(&((*PServidor)->Impressora));
	if ((*PServidor)->Relatorio != NULL)
		TRelatorio_Destruir(&(*PServidor)->Relatorio);
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
	Servidor->Relatorio = TRelatorio_Criar(Servidor->Impressora->TotalPrioridades);
	
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
	TRelatorio_Emitir(Servidor->Relatorio, Servidor->ArquivoSaida);		
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
