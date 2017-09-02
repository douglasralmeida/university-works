/*  JOOGO AMEACA TERRORISTA
	CODIGO FONTE
	
	PRINCIPAL.C - ARQUIVO PRINCIPAL
	DEZEMBRO DE 2015
*/
//CABECALHOS
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <wctype.h>
#include <windows.h>
#include <commctrl.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include "allegro5/allegro_primitives.h"
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_windows.h>
#include "video.h"
#include "recursos.h"
#include "funcoes.h"
#include "menu.h"
#include "janelas.h"
#include "jogo.h"

//VARIAVEIS GLOBAIS
#define LARGURA_X		800
#define ALTURA_Y		600

//FUNCAO COMMCTRLINIT
//Inicializa a biblioteca de controle comuns do Windows.
//
//Parametros: (nenhum)
//Retorno: (nenhum)
void CommctrlInit()
{
	INITCOMMONCONTROLSEX icex;
	icex.dwSize = sizeof(INITCOMMONCONTROLSEX);
	icex.dwICC = ICC_STANDARD_CLASSES;
	InitCommonControlsEx(&icex);
}

//FUNCAO JOGO_INIT
//Inicializa modulos e recursos que serao utilizados no jogo.
//
//Parametros: (nenhum)
//Retorno: tela=Ponteiro para a tela
int jogo_init(ALLEGRO_DISPLAY* tela)
{	
	//Grava o caminho do executavel
	GetCurrentDirectory(MAX_PATH, Application.FilePath);
	//Inicializa a biblioteca Allegro
	if (!al_init())
	{
		return FALSE;
	}
	//Cria a tela
	tela = al_create_display(LARGURA_X, ALTURA_Y);
	if (!tela)
	{
		return FALSE;
	}
	//Esconde o cursor
	al_hide_mouse_cursor(tela);
	//Grava os dados da tela
	Application.Screen = tela;
	Application.ScreenHeight = ALTURA_Y;
	Application.ScreenWidth = LARGURA_X;
	//Altera o titulo da janela
	if (Application.DebugMode == TRUE)
		al_set_window_title(tela, "Ameaça Terrorista - MODO DE DEPURACAO");
	else
		al_set_window_title(tela, "Ameaça Terrorista");
	//Grava o identificador da janela
	Application.MainWindowHandle = al_get_win_window_handle(tela);
	if (!Application.MainWindowHandle)
	{
		return FALSE;
	}
	//Coloca um icone na janela da tela
	HICON Icone, IconePeq;
	Icone = CarregarIcone(IDI_APPICON, TRUE);
	IconePeq = CarregarIcone(IDI_APPICON, FALSE);
	if ((Icone) && (IconePeq))
	{
		SendMessage(Application.MainWindowHandle, WM_SETICON, ICON_BIG, (LPARAM) Icone);
		SendMessage(Application.MainWindowHandle, WM_SETICON, ICON_SMALL, (LPARAM) IconePeq);
	}
	else
	{
        ErroPadronizado(IDS_ERROICORESOURCE);
		return FALSE;
	}
	//Inicaliza o suporte para audio
	al_install_audio();	
	//Inicaliza o suporte para codec de audio
	al_init_acodec_addon();
	//Inicializa o modulo Allegro que carrega as fontes
	al_init_font_addon();
	//Inicializa o modulo Allegro que manipula arquivos de fontes TTF/OTF
	al_init_ttf_addon();
	//Inicializa o modulo Allegro que permite carregar imagens no jogo
	al_init_image_addon();
	//Inicializa o modulo de Desenho
	al_init_primitives_addon();	
	//Inicializa o suporte a teclado
	al_install_keyboard();
	//Inicializa o suporte a mouse
	al_install_mouse();	
	
	return TRUE;
}

//FUNCAO JOGO_INTRO
//Carrega e exibe logotipos e video de introducao
//
//Parametros: (nenhum)
//Retorno: (nenhum)
void jogo_intro(void)
{
	WCHAR* File = L"\\recursos\\videos\\intro.mp4";	
	wcscat(Application.FilePath, File);
	
	//exibir logo
	ALLEGRO_BITMAP *image = al_load_bitmap("recursos\\imagens\\logo.png");
	if (image == NULL)
		ErroSimples(L"O arquivo de imagem nao pode ser reproduzido.");
	else
	{
		//coloca na tela a imagem armazenada na variavel image nas posicoes x=50, y=100
		al_draw_bitmap(image, 0, 0, 0);
		//atualiza a tela
		al_flip_display();
		//pausa a tela por 5 segundos
		al_rest(5.0);
		//destroi a variavel imagem = libera a memoria alocada para ela
		al_destroy_bitmap(image);
		//atualiza a tela
		al_flip_display();	
	}

	//reproduzir video
	if (Application.DebugMode == FALSE)
		if (ReproduzirVideo(Application.MainWindowHandle, Application.FilePath) == MD_FALHA)
			ErroSimples(L"O arquivo de video nao pode ser reproduzido.");
}

//FUNCAO JOGO_MENU
//Carrega e exibe os menus do jogo
//
//Parametros: (nenhum)
//Retorno: TRUE para carregar o jogo, FALSE para sair do jogo.
int jogo_menu(void)
{
	int CarregarJogo = FALSE;
	int ContinuarMenu = TRUE;
	int EstaTocando = FALSE;
	int JanelaResultado = -1;
	int MenuResultado = -1;
	int VoltarInicio;
	ALLEGRO_SAMPLE *melodia_fundo;
	ALLEGRO_SAMPLE_ID melodia_id;

	//Reproduz a melodia de fundo
	al_reserve_samples(2);
	melodia_fundo = al_load_sample("recursos\\melodias\\menu.ogg");
	if (!melodia_fundo)
	{
		//ops....
        ErroSimples(L"O arquivo de audio nao pode ser reproduzido.");
    }
	if (Application.Config.TocarMusica)
	{
		al_play_sample(melodia_fundo, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, &melodia_id);
		EstaTocando = TRUE;
	}

	//Exibe o cursor do mouse
	al_show_mouse_cursor(Application.Screen);

	//Exibe o menu
	while ((ContinuarMenu) && (Application.ClosingAll == FALSE))
	{
		MenuResultado = JanelaPrincipal_Exibir();
		switch (MenuResultado)
		{
			case CMD_NOVOJOGO:
				VoltarInicio = FALSE;
				while ((!VoltarInicio) && (Application.ClosingAll == FALSE))
				{
					JanelaResultado = JanelaDificuldade_Exibir(&Application.Config.GameLevel);
					if (JanelaResultado == jrOK)
					{
						VoltarInicio = TRUE;
						ContinuarMenu = FALSE;
						CarregarJogo = TRUE;
					}
					else if (JanelaResultado == jrCancelar)
					{
						VoltarInicio = TRUE;
					}
				}
			break;
			case CMD_ABRIRJOGO:
				JanelaAbrir_Exibir();
			break;
			case CMD_OPCOES:
				JanelaOpcoes_Exibir(&(Application.Config.TocarSom), &(Application.Config.TocarMusica));
				if ((!EstaTocando) && (Application.Config.TocarMusica))
				{
					al_play_sample(melodia_fundo, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, 0);
					EstaTocando = TRUE;
				}
				else if ((EstaTocando) && (!Application.Config.TocarMusica))
				{
					al_stop_sample(&melodia_id);
					EstaTocando = FALSE;
				}
			break;
			case CMD_AJUDA:
				JanelaAjuda_Exibir();
			break;
			case CMD_SAIR:
				CarregarJogo = FALSE;
				if (!Application.ClosingAll)
					ContinuarMenu = !Pergunta(
								L"Voc\x00ea tem certeza que deseja encerrar o jogo?", 
								L"Sim, encerrar o jogo", 
								L"N\u00e3o, continuar no jogo"
								);
				if (!ContinuarMenu)
					Application.ClosingAll = TRUE;
			break;
		}
	}
	//limpa a memoria alocada
	al_destroy_sample(melodia_fundo);
	return CarregarJogo;
}

//FUNCAO JOGO_MAIN
//Carrega o jogo em si, com as fases, mapas e personagens.
//
//Parametros: (nenhum)
//Retorno: TRUE para zerou, FALSE para perdeu.
int jogo_main(void)
{
	int venceu = TRUE;
	TJogo* Jogo;

	if (Application.Config.GameLevel == GL_FACIL)
		Jogo = JogoCriar(moFacil);
	else
		Jogo = JogoCriar(moDificil);
	if (Jogo != NULL)
	{		
		if (JogoAbrir(Jogo))
		{
			while ((Jogo->FaseAtualID < Jogo->QuantFases) && (venceu == TRUE))
			{
				if (JogoIniciar(Jogo))
				{
					if (JogoChecarDados(Jogo))
						venceu = JogoControlar(Jogo);
					JogoLimpar(Jogo);
				}
				else
				{
					ErroSimples(L"Ocorreu um erro ao carregar os dados da proxima fase do jogo.");
					JogoDestruir(&Jogo);
					return FALSE;
				}
			}
			if ((venceu == TRUE) && (Jogo->FaseAtualID > Jogo->QuantFases))
			{
				ErroSimples(L"Voce eh foda! Zerou o jogo! Bye!");
			}
			JogoDestruir(&Jogo);
		}
		else
		{
			JogoDestruir(&Jogo);
			ErroSimples(L"Ocorreu um erro ao carregar os dados jogo.\n");
			return FALSE;
		}
	}
	else
	{
		ErroSimples(L"Nao foi possivel alocar memoria para o jogo ser executado.\n");
		return FALSE;		
	}
	return venceu;
}

//FUNCAO JOGO_FIM
//Finaliza modulos utilizados no jogo.
//
//Parametros: (nenhum)
//Retorno: tela=Tela do aplicativo
void jogo_fim(ALLEGRO_DISPLAY* tela)
{
	al_show_mouse_cursor(tela);
	//destroi a tela criada para o jogo
	if (tela != NULL)
		al_destroy_display(tela);
}

//FUNCAO PRINCIPAL
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR lpCmdLine, int nCmdShow)
{	
	ALLEGRO_DISPLAY* display = NULL;
	int ExibirMenu = TRUE;
	
	Application.DebugMode = FALSE;
	//Controle global de saida
	Application.ClosingAll = FALSE;
	
	//Ativa o suporte aos controles comums do Windows
	CommctrlInit();
	
	//Interpretador dos comandos passados como argumentos
	if (!wcscmp(lpCmdLine, L"/?"))
	{
		ExibirArgOpcoes();
		return EXIT_SUCCESS;
	}
	else if ((!wcscmp(lpCmdLine, L"/D")) || (!wcscmp(lpCmdLine, L"/d")))
	{
		Application.DebugMode = TRUE;
	}
	
	//Carrega configurações do jogo
	Application.Config.TocarSom = 1;
	Application.Config.TocarMusica = 1;
	Application.Config.GameLevel = GL_FACIL;
	
	//Inicia o jogo
	if (!jogo_init(display))
	{
		jogo_fim(display);
		exit(EXIT_FAILURE);
	}
	jogo_intro();
	while ((ExibirMenu) && (!Application.ClosingAll))
	{
		if (jogo_menu())
		{
			jogo_main();
			ExibirMenu = TRUE;
		}
		else
		{
			ExibirMenu = FALSE;
		}
	}
	jogo_fim(display);
	
	//ACABOU!!!
	exit(EXIT_SUCCESS);	
}
#pragma GCC diagnostic pop