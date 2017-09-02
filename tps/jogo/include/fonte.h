#ifndef _FONTE_H_
#define _FONTE_H_

#include <allegro5/allegro_font.h>

#define FONTE_JANELA 0
#define FONTE_MENU 1
#define FONTE_TEXTO 2

typedef struct 
{
	ALLEGRO_FONT** Fontes;
	int FonteCont;
} TFonteBuffer;

TFonteBuffer* FonteBufferCriar(int QuantFontes);
void FonteBufferDestruir(TFonteBuffer** PBufferFontes);
void FonteBufferAdic(TFonteBuffer* BufferFontes, char* ArquivoFonte, int Tamanho);

#endif