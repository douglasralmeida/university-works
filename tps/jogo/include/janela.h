#ifndef _JANELA_H_
#define _JANELA_H_

#include <allegro5/allegro.h>
#include "menu.h"

typedef struct {
	char* BitmapArquivo;
	ALLEGRO_MOUSE_CURSOR* Cursor;
	TJanelaResultado JanelaResultado;
	TMenu* Menu;
	char* Rotulo;
	int* Teclas;
	int TeclasCount;
	char** Texto;
	int TextoCount;
} TJanela;

TJanela* JanelaCriar(void);
void JanelaDestruir(TJanela** PJanela);
int JanelaExibir(TJanela* Janela);
void JanelaSetBitmap(TJanela* Janela, char* ArquivoBitmap);
void JanelaMenuCriar(TJanela* Janela, int QuantidadeMenus);
void JanelaMenuAdic(TJanela* Janela, char* Rotulo, TMenuTipo Tipo, void* Valor, char** Opcoes, TJanelaResultado Resultado);
void JanelaSetRotulo(TJanela* Janela, char* NovoRotulo);
void JanelaSetTeclas(TJanela* Janela, int QuantidadeTeclas, int* Teclas);
void JanelaTextoAdic(TJanela* Janela, char* Texto);
void JanelaTextoCriar(TJanela* Janela, int QuantidadeLinhas);
#endif