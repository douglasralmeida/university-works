#include <string.h>
#include <unistd.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include "funcoes.h"
#include "teclado.h"
#include "menu.h"

void ExibirItemSimples(ALLEGRO_FONT* fonte, char* Rotulo, int Altura, int EstaMarcado)
{
	ALLEGRO_COLOR corBranca = al_map_rgb(255, 255, 255);
	ALLEGRO_COLOR corVermelha = al_map_rgb(255, 200, 10);
	
	ALLEGRO_COLOR corMenu;
	if (EstaMarcado)
		corMenu = corVermelha;
	else
		corMenu = corBranca;
	al_draw_text(fonte, corMenu, 160, Altura, 0, Rotulo);
}

void ExibirItemOpcoes(ALLEGRO_FONT* fonte, char* Rotulo, char** Opcao, int Altura, int EstaMarcado, int Sim)
{
	ALLEGRO_COLOR corBranca = al_map_rgb(255, 255, 255);
	ALLEGRO_COLOR corVermelha = al_map_rgb(255, 200, 10);
	ALLEGRO_COLOR corMenu, corSim, corNao;
	int PosicaoTexto = 160;
	int PosicaoSim = 330;
	int PosicaoNao = 420;
	
	if (EstaMarcado)
		corMenu = corVermelha;
	else
		corMenu = corBranca;
	if (Sim)
	{
		corSim = corVermelha;
		corNao = corBranca;
	}
	else
	{
		corSim = corBranca;
		corNao = corVermelha;
	}
	al_draw_text(fonte, corMenu, PosicaoTexto, Altura, 0, Rotulo);
	al_draw_text(fonte, corSim, PosicaoTexto + PosicaoSim, Altura, 0, Opcao[0]);
	al_draw_text(fonte, corNao, PosicaoTexto + PosicaoNao, Altura, 0, Opcao[1]);		
}

TMenu* MenuCriar(int QuantidadeMenus)
{
	TMenu* NovoMenu;
	
	NovoMenu = (TMenu*)malloc(sizeof(TMenu));
	NovoMenu->Altura = 0;
	NovoMenu->MenuCont = QuantidadeMenus;
	NovoMenu->Itens = (TMenuItem*)malloc(QuantidadeMenus * sizeof(TMenuItem));
	NovoMenu->ProxItem = 0;
	
	return NovoMenu;
}

void MenuDestruir(TMenu** PMenu)
{
	int i;
	
	if ((*PMenu)->Itens != NULL)
	{
		for (i = 0; i < (*PMenu)->MenuCont; i++)
		{
			if ((*PMenu)->Itens[i].Opcao1 != NULL)
				free((*PMenu)->Itens[i].Opcao1);
			if ((*PMenu)->Itens[i].Opcao2 != NULL)
				free((*PMenu)->Itens[i].Opcao2);
			if ((*PMenu)->Itens[i].Rotulo != NULL)
				free((*PMenu)->Itens[i].Rotulo);
		}
		free((*PMenu)->Itens);
	}
	free(*PMenu);
	*PMenu = NULL;
}

void MenuExibir(TMenu* Menu, ALLEGRO_FONT* Fonte, int IndiceSelecao)
{
	const int ItemMenuAltura = 60;
	int i;
	int EstaMarcado = 0;
	int ItemAltura;
	char** Opcoes;

	//desenha menu a menu
	for (i = 0; i < Menu->MenuCont; i++)
	{
		EstaMarcado = (i == IndiceSelecao);
		ItemAltura = Menu->Altura + ItemMenuAltura * i;
		if (Menu->Itens[i].Tipo == mtSimples)
			ExibirItemSimples(Fonte, Menu->Itens[i].Rotulo, ItemAltura, EstaMarcado);
		else if (Menu->Itens[i].Tipo == mtOpcao)
		{
			Opcoes = (char**)malloc(2 * sizeof(char*));
			Opcoes[0] = Menu->Itens[i].Opcao1;
			Opcoes[1] = Menu->Itens[i].Opcao2;
			ExibirItemOpcoes(Fonte, Menu->Itens[i].Rotulo, Opcoes, ItemAltura, EstaMarcado, *((int*)Menu->Itens[i].Valor));
			free(Opcoes);
		}
		else if (Menu->Itens[i].Tipo == mtComando)
			ExibirItemSimples(Fonte, Menu->Itens[i].Rotulo, ItemAltura, EstaMarcado);
	}
}
	
void MenuInserir(TMenu* Menu, char* Rotulo, TMenuTipo Tipo, void* Valor, char* Opcoes[2], TJanelaResultado Resultado)
{
	int TamanhoRotulo;
	
	if (Menu->Itens != NULL)
	{
		if (Menu->ProxItem < Menu->MenuCont)
		{
			TamanhoRotulo = strlen(Rotulo) + 1;
			if (Opcoes != NULL)
			{
				Menu->Itens[Menu->ProxItem].Opcao1 = (char*)malloc(strlen(Opcoes[0]) * sizeof(char) + 1);
				strcpy(Menu->Itens[Menu->ProxItem].Opcao1, Opcoes[0]);
				Menu->Itens[Menu->ProxItem].Opcao2 = (char*)malloc(strlen(Opcoes[1]) * sizeof(char) + 1);
				strcpy(Menu->Itens[Menu->ProxItem].Opcao2, Opcoes[1]);
			}
			Menu->Itens[Menu->ProxItem].Resultado = Resultado;
			Menu->Itens[Menu->ProxItem].Rotulo = (char*)malloc(TamanhoRotulo * sizeof(char));
			strcpy(Menu->Itens[Menu->ProxItem].Rotulo, Rotulo);
			Menu->Itens[Menu->ProxItem].Tipo = Tipo;
			Menu->Itens[Menu->ProxItem].Valor = Valor;
			Menu->ProxItem++;
		}
	}
}