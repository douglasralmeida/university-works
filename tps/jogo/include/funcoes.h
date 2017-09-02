#ifndef _FUNCOES_H_
#define _FUNCOES_H_

#include <wchar.h>
#include <windows.h>
#include <allegro5/allegro.h>

#define GL_FACIL 1
#define GL_DIFICIL 0

#define REC_NENHUM 0
#define REC_MAPA 1
#define REC_FASE 2
#define REC_PERSON 3
#define REC_IMAGEM 4
#define REC_GRAFICO 5
#define REC_MELODIA 6
#define REC_SOM 7
#define REC_VIDEO 8
#define REC_FONTE 9
#define REC_CURSOR 10
#define REC_GRAFICO_MAPA 51
#define REC_GRAFICO_PERSON 53

typedef struct _TConfig{
	int GameLevel;
	int TocarMusica;
	int TocarSom;
} TConfig;

typedef struct _TApplication{
	int ClosingAll;
	TConfig Config;
	int DebugMode;
	HWND MainWindowHandle;
	WCHAR FilePath[MAX_PATH];
	ALLEGRO_DISPLAY* Screen;
	int ScreenWidth;
	int ScreenHeight;
} TApplication;

extern TApplication Application;

HICON CarregarIcone(int IconeID, int EhGrande);

int CarregarString(int StringID, WCHAR* Texto);

void ErroPadronizado(const int ErroCodigo);

void ErroSimples(WCHAR* Texto);

void ExibirArgOpcoes(void);

void ExibirMensagem(const WCHAR* Tipo, WCHAR* Texto, WCHAR* SubTexto);

int Pergunta(WCHAR* Texto, WCHAR* Botao1, WCHAR* Botao2);

char* ReceberRecDirCompleto(int RecursoTipo, char* Recurso);

#endif
