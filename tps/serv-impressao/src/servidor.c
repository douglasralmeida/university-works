{/*
**	SERVIDOR 
**	DOUGLAS RODRIGUES DE ALMEIDA
**
**	Implementacao do servidor
*/

#include "lista.h"
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
	
	return TServidor;
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
	if (fgets(buffer, BUFFER_TAMANHO, TServidor->ArquivoEntrada) != NULL)
		if (BufferImpressora(Servidor, buffer))
			while ((encerraanalise == false) || (buffer, BUFFER_TAMANHO, Servidor->ArquivoEntrada))
				encerraanalise = BufferAnalisar(Servidor, buffer);
		else	
			printf("Erro (0x101): Erro ao abrir arquivo de entrada de dados.\n");
	}
	else
		printf("Erro (0x102): Erro ao abrir arquivo de entrada de dados.\n");
}

bool TServidor_CadastrarImpressora(TServidor* Servidor, char* Impressora, int Capacidade, int Escalonador)
{
	Servidor->Impressora = malloc(sizeof(TImpressora));
	if (Servidor->Impressora == NULL)
		return false;
	
	strcpy(Servidor->Impressora->Nome, Impressora);
	Servidor->Impressora->Capacidade = Capacidade;
	Servidor->Impressora->Escalonador = Escalonador;
	
	return true;
}

bool TServidor_Finalizar(TServidor* Servidor)
{
	fclose(Servidor->ArquivoEntrada);
	fclose(Servidor->ArquivoSaida);
}

void TServidor_Imprimir(TServidor* Servidor, const char* Nome, const int Hora, const int Prioridade, const int Paginas, const int TempoMaximo)
{
	printf("Imprimir\n");
}

bool TServidor_Preparar(TServidor* Servidor, const char* NomeArquivoEntrada, const char* NomeArquivoSaida)
{
	Servidor->ArquivoEntrada = fopen(NomeArquivoEntrada , "rt");
	Servidor->ArquivoSaida = fopen(NomeArquivoSaida , "wt");
	
	return ((Servidor->AbrirEntrada != NULL) && (Servidor->ArquivoSaida != NULL));
}

void TServidor_Relatorio(TServidor* Servidor)
{
	printf("Relatorio\n");
}

void TServidor_UsuarioExcluir(TServidor* Servidor, const char* Nome)
{
	TListaNo* No;
	TUsuario* Usuario;
	
	Usuario = TUsuario_Criar(Nome, 0);
	No = TLista_Pesquisar(Servidor->Usuarios, Usuario);
	TLista_Remover(Servidor->Usuarios, No);
	TUsuario_Destruir(&Usuario);
}

void TServidor_UsuarioNovo(TServidor* Servidor, const char* nome, const int Prioridade)
{
	TUsuario* Usuario;
	
	Usuario = TUsuario_Criar(Nome, Prioridade);
	TLista_Adicionar(Servidor->Usuarios, Usuario);
}