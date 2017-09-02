#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <commctrl.h>
#include "funcoes.h"

TApplication Application;

HICON CarregarIcone(int IconeID, int EhGrande)
{
	int IconSize;
	if (EhGrande)
		IconSize = 32;
	else
		IconSize = 16;
	return (HICON)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IconeID), IMAGE_ICON, IconSize, IconSize, 0);		
}

int CarregarString(int StringID, WCHAR* Texto)
{
	return LoadString(GetModuleHandle(NULL), StringID, Texto, sizeof(WCHAR) * sizeof(Texto));
}

void ErroPadronizado(const int CodigoErro)
{
	WCHAR Mensagem[256];
	WCHAR SubMensagem[256];
	if (CarregarString(CodigoErro, Mensagem) && CarregarString(CodigoErro, SubMensagem))
		ExibirMensagem(TD_ERROR_ICON, Mensagem, SubMensagem);
	else
		ErroSimples(L"Erro ao carregar um recurso.");
}

void ErroSimples(WCHAR* Texto)
{
	ExibirMensagem(TD_ERROR_ICON, Texto, NULL);
}

void ExibirArgOpcoes()
{
	WCHAR* Titulo = L"canalha.exe";
	WCHAR* Texto = L"Comandos disponiveis:\x000A\x0009- /D ou /d: Executa o jogo no modo de depuracao.\x000A\x0009- /?: Exibe a janela de ajuda de linha de comando.";
	
	ExibirMensagem(TD_INFORMATION_ICON, Titulo, Texto);
}

void ExibirMensagem(const WCHAR* Tipo, WCHAR* Texto, WCHAR* SubTexto)
{
	TaskDialog(
		Application.MainWindowHandle,
		NULL,
		L"Erro",
		Texto,
		SubTexto,
		TDCBF_OK_BUTTON,
		Tipo,
		NULL
	);
}

int Pergunta(WCHAR* Texto, WCHAR* Botao1, WCHAR* Botao2)
{
	int BotaoSelecionado = 0;
	TASKDIALOGCONFIG MsgDialogo = {0};
	const TASKDIALOG_BUTTON Botoes[] =
										{
											{IDYES, Botao1},
											{IDNO, Botao2}
										};
	MsgDialogo.cbSize = sizeof(MsgDialogo);
	MsgDialogo.hwndParent = Application.MainWindowHandle;
	MsgDialogo.dwFlags = TDF_USE_COMMAND_LINKS;
	MsgDialogo.pszWindowTitle = L"Pergunta";
	MsgDialogo.pszMainIcon = TD_INFORMATION_ICON;
	MsgDialogo.pszMainInstruction = Texto;
	MsgDialogo.pButtons = Botoes;
	MsgDialogo.cButtons = ARRAYSIZE(Botoes);

	TaskDialogIndirect(&MsgDialogo, &BotaoSelecionado, NULL, NULL);

	if (BotaoSelecionado == IDYES)
		return 1;
	else
		return 0;
}

char* ReceberRecDir(int RecursoTipo)
{
	char* Result;
	switch (RecursoTipo)
	{
		case REC_NENHUM:
			Result = (char*)malloc(sizeof(char));
			Result[0] = '\0';
			return Result;
		break;
		case REC_MAPA:
			Result = (char*)malloc(18 * sizeof(char));
			strcpy(Result, "recursos\\mapas\\");
			return Result;
		break;
		case REC_FASE:
			Result = (char*)malloc(18 * sizeof(char));
			strcpy(Result, "recursos\\fases\\");
			return Result;
		break;
		case REC_PERSON:
			Result = (char*)malloc(24 * sizeof(char));
			strcpy(Result, "recursos\\personagens\\");
			return Result;
		break;
		case REC_IMAGEM:
			Result = (char*)malloc(20 * sizeof(char));
			strcpy(Result, "recursos\\imagens\\");
			return Result;
		break;
		case REC_GRAFICO:
			Result = (char*)malloc(21 * sizeof(char));
			strcpy(Result, "recursos\\graficos\\");
			return Result;
		break;
		case REC_MELODIA:
			Result = (char*)malloc(21 * sizeof(char));
			strcpy(Result, "recursos\\melodias\\");
			return Result;
		break;
		case REC_SOM:
			Result = (char*)malloc(17 * sizeof(char));
			strcpy(Result, "recursos\\sons\\");
			return Result;
		break;
		case REC_VIDEO:
			Result = (char*)malloc(19 * sizeof(char));
			strcpy(Result, "recursos\\videos\\");
			return Result;
		break;
		case REC_FONTE:
			Result = (char*)malloc(19 * sizeof(char));
			strcpy(Result, "recursos\\fontes\\");
			return Result;		
		break;
		case REC_CURSOR:
			Result = (char*)malloc(21 * sizeof(char));
			strcpy(Result, "recursos\\cursores\\");
			return Result;		
		break;
		case REC_GRAFICO_MAPA:
			Result = (char*)malloc(27 * sizeof(char));
			strcpy(Result, "recursos\\graficos\\mapa\\");
			return Result;
		break;
		case REC_GRAFICO_PERSON:
			Result = (char*)malloc(33 * sizeof(char));
			strcpy(Result, "recursos\\graficos\\personagem\\");
			return Result;
		break;
	}
	return NULL;
}

char* ReceberRecDirCompleto(int RecursoTipo, char* Recurso)
{
	int i;
	char* DirCaminho;
	char* EnderecoArquivo;

	DirCaminho = ReceberRecDir(RecursoTipo);
	i = strlen(DirCaminho) + strlen(Recurso) + 1;
	EnderecoArquivo = (char*)malloc(i * sizeof(char));
	strcpy(EnderecoArquivo, DirCaminho);
	free(DirCaminho);
	strcat(EnderecoArquivo, Recurso);
	return EnderecoArquivo;
}
