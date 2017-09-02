#ifndef _GRAFICOS_H_
#define _GRAFICOS_H_

#include <allegro5/allegro.h>
#include "tipos.h"

typedef struct {
	ALLEGRO_BITMAP** Armas;
	ALLEGRO_MOUSE_CURSOR** Cursores;
	ALLEGRO_BITMAP** Mapas;
	ALLEGRO_BITMAP* Mundo;
	ALLEGRO_BITMAP* Pernas;
	ALLEGRO_BITMAP** Personagens;
	TPonto* CursorFoco;
	int ArmaCont;
	int CursorCont;
	int MapaCont;
	int PersonCont;
} TBitmapBuffer;

typedef struct {
	int EscalaVermelho;
	int EscalaVerde;
	int EscalaAzul;
} TCor;

TBitmapBuffer* BitmapBufferCriar(void);
void BitmapBufferDestruir(TBitmapBuffer** PBufferBitmaps);
void BitmapBufferAdicArmas(TBitmapBuffer* BufferBitmaps, int QuantArmas, char** ArquivosArmas);
void BitmapBufferAdicCursores(TBitmapBuffer* BufferBitmaps, int QuantCursores, char** ArquivosCursores, TPonto*Focos);
void BitmapBufferAdicMapa(TBitmapBuffer* BufferBitmaps, int QuantMascaras, char** ArquivosMapa);
void BitmapBufferAdicPernas(TBitmapBuffer* BufferBitmaps);
void BitmapBufferAdicPerson(TBitmapBuffer* BufferBitmaps, int QuantPerson, char** ArquivosPerson);
void BitmapBufferConstruirMundo(TBitmapBuffer* BufferBitmaps, int** Mascara, int XMax, int YMax);

void AlvoDesenhoConfig(ALLEGRO_BITMAP* Bitmap);
void AlvoDesenhoRestaurar(void);

void BitmapRotativoTransparenteDesenhar(ALLEGRO_BITMAP* Bitmap, TPonto* Posicao, int Transparencia, float Angulo);
void BitmapRotativoDesenhar(ALLEGRO_BITMAP* Bitmap, TPonto* Posicao, float Angulo);

void TelaAtualizar(void);
void TelaColorir(TCor Cor);	
void TelaDesenhar(ALLEGRO_BITMAP* Bitmap, TPonto* Posicao);
void TelaDesenharTransparencia(ALLEGRO_BITMAP* Bitmap,  TPonto* Posicao, int Transparencia);
void TelaRegiaoDesenhar(ALLEGRO_BITMAP* Bitmap, TPonto* PontoInicial, int Largura, int Altura);

#endif