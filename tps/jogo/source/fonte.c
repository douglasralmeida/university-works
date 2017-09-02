#include <stdio.h>
#include <allegro5/allegro.h>
#include "funcoes.h"
#include "fonte.h"

TFonteBuffer* FonteBufferCriar(int QuantFontes)
{
	int i;
	TFonteBuffer* NovoBufferFontes;
	
	NovoBufferFontes = (TFonteBuffer*)malloc(sizeof(TFonteBuffer));
	NovoBufferFontes->Fontes = (ALLEGRO_FONT**)malloc(sizeof(ALLEGRO_FONT*)*QuantFontes);
	NovoBufferFontes->FonteCont = QuantFontes;
	for (i = 0; i < QuantFontes; i++)
		NovoBufferFontes->Fontes[i] = NULL;
	
	return NovoBufferFontes;
}

void FonteBufferDestruir(TFonteBuffer** PBufferFontes)
{
	int i;
	
	if ((*PBufferFontes)->Fontes != NULL)
	{
		for (i = 0; i < (*PBufferFontes)->FonteCont; i++)
		{
			al_destroy_font((*PBufferFontes)->Fontes[i]);
		}
		free((*PBufferFontes)->Fontes);
	}
	free(*PBufferFontes);
	*PBufferFontes = NULL;
}

void FonteBufferAdic(TFonteBuffer* BufferFontes, char* ArquivoFonte, int Tamanho)
{
	int i = 0;
	char* Caminho;

	while (BufferFontes->Fontes[i] != NULL)
		i++;
	Caminho = ReceberRecDirCompleto(REC_FONTE, ArquivoFonte);
	BufferFontes->Fontes[i] = al_load_font(Caminho, Tamanho, 1);
	free(Caminho);
}