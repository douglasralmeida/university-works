#include <string.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_font.h>
#include "vetor.h"
#include "funcoes.h"
#include "audio.h"
#include "fonte.h"
#include "teclado.h"
#include "menu.h"
#include "janela.h"

#define TRUE 1
#define FALSE 0

TJanela* JanelaCriar(void)
{
	char* Caminho;
	ALLEGRO_BITMAP* bitmap;
	TJanela* NovaJanela;
	
	NovaJanela = (TJanela*)malloc(sizeof(TJanela));
	if (NovaJanela == NULL)
		return NULL;
	NovaJanela->BitmapArquivo = NULL;
	NovaJanela->JanelaResultado = jrNada;
	NovaJanela->Menu = NULL;
	NovaJanela->Rotulo = NULL;
	NovaJanela->Teclas = NULL;
	NovaJanela->TeclasCount = 0;
	NovaJanela->Texto = NULL;
	NovaJanela->TextoCount = 0;
	
	Caminho = ReceberRecDirCompleto(REC_CURSOR, "cursor1.png");
	if (Caminho == NULL)
	{
		free(NovaJanela);
		return NULL;
	}
	bitmap = al_load_bitmap(Caminho);
	if (bitmap == NULL)
	{
		free(NovaJanela);
		return NULL;		
	}
	NovaJanela->Cursor = al_create_mouse_cursor(bitmap, 0, 0);
	al_destroy_bitmap(bitmap);
	free(Caminho);

	return NovaJanela;
}

void JanelaDestruir(TJanela** PJanela)
{
	if ((*PJanela)->BitmapArquivo != NULL)
		free((*PJanela)->BitmapArquivo);
	if ((*PJanela)->Cursor != NULL)
		al_destroy_mouse_cursor((*PJanela)->Cursor);
	if ((*PJanela)->Menu != NULL)
		MenuDestruir(&(*PJanela)->Menu);
	if ((*PJanela)->Rotulo != NULL)
		free((*PJanela)->Rotulo);
	if ((*PJanela)->Teclas != NULL)
		free((*PJanela)->Teclas);
	if ((*PJanela)->Texto != NULL)
		MatrizDestruir((void***)&(*PJanela)->Texto, (*PJanela)->TextoCount);

	free(*PJanela);
	*PJanela = NULL;
}

int JanelaExibir(TJanela* Janela)
{
	int i;
	char* Caminho;
	int menu_selec = 0;
	int sai_menu = FALSE;
	int tecla;
	ALLEGRO_BITMAP* JanelaImgFundo;
	ALLEGRO_SAMPLE *som_menu;
	ALLEGRO_COLOR corBranca = al_map_rgb(255, 255, 255);

	//altera o cursor do mouse
	al_set_mouse_cursor(Application.Screen, Janela->Cursor);
	
	//carrega as fontes usadas pelo menu na memoria
	TFonteBuffer* BufferFontes = FonteBufferCriar(3);
	if (BufferFontes == NULL)
		return jrCancelar;
	FonteBufferAdic(BufferFontes, "titulo.ttf", 100);
	FonteBufferAdic(BufferFontes, "menu.ttf", 35);
	FonteBufferAdic(BufferFontes, "texto.ttf", 14);

	//carrega a imagem de fundo do menu
	Caminho = ReceberRecDirCompleto(REC_IMAGEM, Janela->BitmapArquivo);
	JanelaImgFundo = al_load_bitmap(Caminho);
	free(Caminho);
	if (!JanelaImgFundo)
	{
		ErroSimples(L"O arquivo de imagem nao pode ser acessado.");
		return FALSE;
	}
	//carrega o audio para o som do menu
	som_menu = al_load_sample("recursos\\sons\\interface\\menu.wav");
	//loop do Menu
	while (!sai_menu)
	{
		//al_clear_to_color(al_map_rgb(0, 0, 0));
		//desenha naJanela->BitmapArquivo tela a imagem de fundo
		al_draw_bitmap(JanelaImgFundo, 0, 0, 0);
		//escreve o titulo
		if (Janela->Rotulo != NULL)
			al_draw_text(BufferFontes->Fontes[0], al_map_rgb(255, 255, 255), 40, 40, 0, Janela->Rotulo);
	
		//desenha o texto
		if (Janela->Texto != NULL)
		{
			for (i = 0; i < Janela->TextoCount; i++)
			{
				al_draw_text(BufferFontes->Fontes[FONTE_TEXTO], corBranca, 220, 160 + 20 * i, 0, Janela->Texto[i]);
			}
		}
		//desenha as opções do menu
		if (Janela->Menu != NULL)
			MenuExibir(Janela->Menu, BufferFontes->Fontes[FONTE_MENU], menu_selec);
		//atualiza a tela
		al_flip_display();
		//aguarda uma tecla ser pressionada
		tecla = AguardaTecla(Janela->Teclas, Janela->TeclasCount);
		switch (tecla)
		{
			case 0: //Para cima
				if (menu_selec > 0)
				{
					menu_selec--;
					TocarSomUnicaVez(som_menu);
				}
			break;
			case 1: //Para baixo
				if (menu_selec < Janela->Menu->MenuCont - 1)
				{
					menu_selec++;
					TocarSomUnicaVez(som_menu);
				}
			break;
			case 2: //Para direita
				if (Janela->Menu->Itens[menu_selec].Tipo == mtOpcao)
					*((int*)Janela->Menu->Itens[menu_selec].Valor) = FALSE;
			break;
			case 3: //Para esquerda
				if (Janela->Menu->Itens[menu_selec].Tipo == mtOpcao)
					*((int*)Janela->Menu->Itens[menu_selec].Valor) = TRUE;
			break;
			case FECHAR_JANELA:			
			case 4: //ESC
				sai_menu = TRUE;
				Janela->JanelaResultado = jrCancelar;
			break;
			case 5: //ENTER
				if (Janela->Menu->Itens[menu_selec].Tipo == mtComando)
				{
					sai_menu = TRUE;
					Janela->JanelaResultado = *((int*)Janela->Menu->Itens[menu_selec].Valor);
				}
				else if (Janela->Menu->Itens[menu_selec].Resultado == jrCancelar)
				{
					sai_menu = TRUE;
					Janela->JanelaResultado = jrCancelar;
				}
				else if (Janela->Menu->Itens[menu_selec].Resultado == jrOK)
				{
					sai_menu = TRUE;
					Janela->JanelaResultado = jrOK;					
				}
			break;
		}		
	}
	//limpa a memoria alocada	
	al_destroy_bitmap(JanelaImgFundo);
	al_destroy_sample(som_menu);
	FonteBufferDestruir(&BufferFontes);

	return Janela->JanelaResultado;
}

void JanelaSetBitmap(TJanela* Janela, char* ArquivoBitmap)
{
	int i;
	
	i = strlen(ArquivoBitmap) + 1;
	Janela->BitmapArquivo = (char*)malloc(i * sizeof(char));
	if (Janela->BitmapArquivo != NULL)
		strcpy(Janela->BitmapArquivo, ArquivoBitmap);
}

void JanelaMenuCriar(TJanela* Janela, int QuantidadeMenus)
{
	Janela->Menu = MenuCriar(QuantidadeMenus);
	if (Janela->Rotulo == NULL)
		Janela->Menu->Altura = 60;
	else
		Janela->Menu->Altura = 180;
}

void JanelaMenuAdic(TJanela* Janela, char* Rotulo, TMenuTipo Tipo, void* Valor, char** Opcoes, TJanelaResultado Resultado)
{
	MenuInserir(Janela->Menu, Rotulo, Tipo, Valor, Opcoes, Resultado);
}

void JanelaSetRotulo(TJanela* Janela, char* NovoRotulo)
{
	int i;
	
	i = strlen(NovoRotulo) + 1;
	Janela->Rotulo = (char*)malloc(i * sizeof(char));
	if (Janela->Rotulo != NULL)
		Janela->Rotulo = NovoRotulo;
}

void JanelaSetTeclas(TJanela* Janela, int QuantidadeTeclas, int* Teclas)
{
	int i;
	
	Janela->Teclas = (int*)malloc(QuantidadeTeclas * sizeof(int));
	if (Janela->Teclas != NULL)
	{
		Janela->TeclasCount = QuantidadeTeclas;
		for (i = 0; i < QuantidadeTeclas; i++)
			Janela->Teclas[i] = Teclas[i];
	}
}

void JanelaTextoAdic(TJanela* Janela, char* Texto)
{
	int i = 0;
	
	if (Janela->Texto != NULL)
	{
		while (strlen(Janela->Texto[i]) > 0)
			i++;
		strncpy(Janela->Texto[i], Texto, 63);
	}
}


void JanelaTextoCriar(TJanela* Janela, int QuantidadeLinhas)
{
	Janela->Texto = CMatrizCriar(QuantidadeLinhas, 64);
	if (Janela->Texto != NULL)
		Janela->TextoCount = QuantidadeLinhas;
}