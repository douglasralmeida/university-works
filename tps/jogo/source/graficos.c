#include <stdio.h>
#include "funcoes.h"
#include "graficos.h"

TBitmapBuffer* BitmapBufferCriar(void)
{
	TBitmapBuffer* NovoBufferBitmaps;
	
	NovoBufferBitmaps = (TBitmapBuffer*)malloc(sizeof(TBitmapBuffer));
	NovoBufferBitmaps->Armas = NULL;
	NovoBufferBitmaps->ArmaCont = 0;
	NovoBufferBitmaps->Cursores = NULL;
	NovoBufferBitmaps->CursorCont = 0;
	NovoBufferBitmaps->CursorFoco = NULL;
	NovoBufferBitmaps->Mapas = NULL;
	NovoBufferBitmaps->MapaCont = 0;
	NovoBufferBitmaps->Mundo = NULL;
	NovoBufferBitmaps->Pernas = NULL;
	NovoBufferBitmaps->Personagens = NULL;
	NovoBufferBitmaps->PersonCont = 0;
	
	return NovoBufferBitmaps;
}

void BitmapBufferDestruir(TBitmapBuffer** PBufferBitmaps)
{
	int i;
	
	if ((*PBufferBitmaps)->Armas != NULL)
	{
		for (i=0; i < (*PBufferBitmaps)->ArmaCont; i++)
		{
			al_destroy_bitmap((*PBufferBitmaps)->Armas[i]);
		}
		free((*PBufferBitmaps)->Armas);
	}
	if ((*PBufferBitmaps)->Cursores != NULL)
	{
		for (i=0; i < (*PBufferBitmaps)->CursorCont; i++)
		{
			al_destroy_mouse_cursor((*PBufferBitmaps)->Cursores[i]);
		}
		free((*PBufferBitmaps)->Cursores);
	}
	if ((*PBufferBitmaps)->Mapas != NULL)
	{
		for (i=0; i < (*PBufferBitmaps)->MapaCont; i++)
		{
			al_destroy_bitmap((*PBufferBitmaps)->Mapas[i]);
		}
		free((*PBufferBitmaps)->Mapas);
	}
	if ((*PBufferBitmaps)->Pernas != NULL)
	{
		al_destroy_bitmap((*PBufferBitmaps)->Pernas);
	}	
	if ((*PBufferBitmaps)->Personagens != NULL)
	{
		for (i=0; i < (*PBufferBitmaps)->PersonCont; i++)
		{
			al_destroy_bitmap((*PBufferBitmaps)->Personagens[i]);
		}
		free((*PBufferBitmaps)->Personagens);
	}
	if ((*PBufferBitmaps)->Mundo != NULL)
	{
		al_destroy_bitmap((*PBufferBitmaps)->Mundo);
	}
	free(*PBufferBitmaps);
	*PBufferBitmaps = NULL;
}

void BitmapBufferAdicArmas(TBitmapBuffer* BufferBitmaps, int QuantArmas, char** ArquivosArmas)
{
	int i;
	char* Caminho;
	
	BufferBitmaps->Armas = (ALLEGRO_BITMAP**)malloc(sizeof(ALLEGRO_BITMAP*)*QuantArmas);
	for (i = 0; i < QuantArmas; i++)
	{
		Caminho = ReceberRecDirCompleto(REC_GRAFICO, ArquivosArmas[i]);
		BufferBitmaps->Armas[i] = al_load_bitmap(Caminho);
		al_convert_mask_to_alpha(BufferBitmaps->Armas[i], al_map_rgb(255, 0, 255));
		al_lock_bitmap(BufferBitmaps->Armas[i], al_get_bitmap_format(BufferBitmaps->Armas[i]), ALLEGRO_LOCK_READONLY);
		BufferBitmaps->ArmaCont++;
		free(Caminho);	
	}
}

void BitmapBufferAdicCursores(TBitmapBuffer* BufferBitmaps, int QuantCursores, char** ArquivosCursores, TPonto*Focos)
{
	int i;
	char* Caminho;
	ALLEGRO_BITMAP* bitmap;
	
	BufferBitmaps->Cursores = (ALLEGRO_MOUSE_CURSOR**)malloc(sizeof(ALLEGRO_MOUSE_CURSOR*)*QuantCursores);
	BufferBitmaps->CursorFoco = (TPonto*)malloc(sizeof(TPonto)*QuantCursores);
	for (i = 0; i < QuantCursores; i++)
	{
		Caminho = ReceberRecDirCompleto(REC_CURSOR, ArquivosCursores[i]);
		bitmap = al_load_bitmap(Caminho);
		BufferBitmaps->Cursores[i] = al_create_mouse_cursor(bitmap, (int)Focos[i].x, (int)Focos[i].y);
		BufferBitmaps->CursorCont++;
		free(Caminho);
		al_destroy_bitmap(bitmap);
	}
}

void BitmapBufferAdicMapa(TBitmapBuffer* BufferBitmaps, int QuantMascaras, char** ArquivosMapa)
{
	int i;
	char* Caminho;

	BufferBitmaps->Mapas = (ALLEGRO_BITMAP**)malloc(sizeof(ALLEGRO_BITMAP*)*QuantMascaras);
	for (i = 0; i < QuantMascaras; i++)
	{
		Caminho = ReceberRecDirCompleto(REC_GRAFICO_MAPA, ArquivosMapa[i]);
		BufferBitmaps->Mapas[i] = al_load_bitmap(Caminho);
		al_lock_bitmap(BufferBitmaps->Mapas[i], al_get_bitmap_format(BufferBitmaps->Mapas[i]), ALLEGRO_LOCK_READONLY);
		BufferBitmaps->MapaCont++;
		free(Caminho);
	}
}

void BitmapBufferAdicPernas(TBitmapBuffer* BufferBitmaps)
{
	char* Caminho;
	
	Caminho = ReceberRecDirCompleto(REC_GRAFICO_PERSON, "pernas.bmp");
	BufferBitmaps->Pernas = al_load_bitmap(Caminho);
	al_convert_mask_to_alpha(BufferBitmaps->Pernas, al_map_rgb(255, 0, 255));
	al_lock_bitmap(BufferBitmaps->Pernas, al_get_bitmap_format(BufferBitmaps->Pernas), ALLEGRO_LOCK_READONLY);
	free(Caminho);
}

void BitmapBufferAdicPerson(TBitmapBuffer* BufferBitmaps, int QuantPerson, char** ArquivosPerson)
{
	int i;
	char* Caminho;
	
	BufferBitmaps->Personagens = (ALLEGRO_BITMAP**)malloc(sizeof(ALLEGRO_BITMAP*)*QuantPerson);
	for (i = 0; i < QuantPerson; i++)
	{
		Caminho = ReceberRecDirCompleto(REC_GRAFICO_PERSON, ArquivosPerson[i]);
		BufferBitmaps->Personagens[i] = al_load_bitmap(Caminho);
		al_convert_mask_to_alpha(BufferBitmaps->Personagens[i], al_map_rgb(255, 0, 255));
		al_lock_bitmap(BufferBitmaps->Personagens[i], al_get_bitmap_format(BufferBitmaps->Personagens[i]), ALLEGRO_LOCK_READONLY);
		BufferBitmaps->PersonCont++;
		free(Caminho);	
	}
}

void BitmapBufferConstruirMundo(TBitmapBuffer* BufferBitmaps, int** Mascara, int XMax, int YMax)
{
	int i;
	int j;
	const int AlturaPiso = 32;
	const int LarguraPiso = 32;

	TPonto Ponto;
		
	BufferBitmaps->Mundo = al_create_bitmap(YMax*LarguraPiso, XMax*AlturaPiso);
	AlvoDesenhoConfig(BufferBitmaps->Mundo);
	for (i = 0; i < XMax; i++)
	{
		for (j = 0; j < YMax; j++)
		{			
			Ponto.x = i*LarguraPiso;
			Ponto.y = j*AlturaPiso;
			TelaDesenhar(BufferBitmaps->Mapas[Mascara[i][j]], &Ponto);	
		}
	}
	AlvoDesenhoRestaurar();
}

void BitmapRotativoTransparenteDesenhar(ALLEGRO_BITMAP* Bitmap, TPonto* Posicao, int Transparencia, float Angulo)
{
	int centro_altura;
	int centro_largura;
	ALLEGRO_COLOR Cor = al_map_rgba(255, 255, 255, Transparencia);

	centro_largura = al_get_bitmap_width(Bitmap) / 2;
	centro_altura = al_get_bitmap_height(Bitmap) / 2;
		
	al_draw_tinted_rotated_bitmap(Bitmap,
							Cor,
							centro_largura, 
							centro_altura, 
							Posicao->x + 16,
							Posicao->y + 16, 
							Angulo, 
							0);
}

void BitmapRotativoDesenhar(ALLEGRO_BITMAP* Bitmap, TPonto* Posicao, float Angulo)
{
	int centro_altura;
	int centro_largura;

	centro_largura = al_get_bitmap_width(Bitmap) / 2;
	centro_altura = al_get_bitmap_height(Bitmap) / 2;
		
	al_draw_rotated_bitmap(Bitmap, 
							centro_largura, 
							centro_altura, 
							Posicao->x + 16,
							Posicao->y + 16, 
							Angulo, 
							0);
}

void TelaAtualizar(void)
{
	al_flip_display();
}

void TelaColorir(TCor Cor)
{
	ALLEGRO_COLOR ACor = al_map_rgb(Cor.EscalaVermelho, Cor.EscalaVerde, Cor.EscalaAzul);	
	al_clear_to_color(ACor);
}

void TelaDesenhar(ALLEGRO_BITMAP* Bitmap, TPonto* Posicao)
{
	al_draw_bitmap(Bitmap, Posicao->y, Posicao->x, 0);
}

void TelaDesenharTransparencia(ALLEGRO_BITMAP* Bitmap, TPonto* Posicao, int Transparencia)
{
	ALLEGRO_COLOR Cor = al_map_rgba(1, 1, 1, Transparencia);
	al_draw_tinted_bitmap(Bitmap, Cor, Posicao->y, Posicao->x, 0);
}

void TelaRegiaoDesenhar(ALLEGRO_BITMAP* Bitmap, TPonto* PontoInicial, int Largura, int Altura)
{
	al_draw_bitmap_region(Bitmap, PontoInicial->x, PontoInicial->y, Largura, Altura, 0, 0, 0);
}

void AlvoDesenhoConfig(ALLEGRO_BITMAP* Bitmap)
{
	al_set_target_bitmap(Bitmap);
}

void AlvoDesenhoRestaurar(void)
{
	al_set_target_backbuffer(Application.Screen);
}