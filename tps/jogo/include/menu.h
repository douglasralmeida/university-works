#ifndef _MENU_H_
#define _MENU_H_

#include <allegro5/allegro_font.h>

typedef enum {jrCancelar, jrOK, jrNada} TJanelaResultado;

typedef enum {mtSimples, mtOpcao, mtComando} TMenuTipo;

typedef struct {
	TJanelaResultado Resultado;
	char* Opcao1;
	char* Opcao2;
	char* Rotulo;
	TMenuTipo Tipo;
	void* Valor;
} TMenuItem;

typedef struct {
	int Altura;
	int MenuCont;
	TMenuItem* Itens;
	int ProxItem;
} TMenu;

TMenu* MenuCriar(int QuantidadeMenus);
void MenuDestruir(TMenu** PMenu);
void MenuExibir(TMenu* Menu, ALLEGRO_FONT* Fonte, int IndiceSelecao);
void MenuInserir(TMenu* Menu, char* Rotulo, TMenuTipo Tipo, void* Valor, char* Opcoes[2], TJanelaResultado Resultado);
#endif