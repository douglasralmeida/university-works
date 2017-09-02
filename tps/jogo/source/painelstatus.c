#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include "tipos.h"
#include "funcoes.h"
#include "graficos.h"
#include "painelstatus.h"

TPainelStatus* PainelStatusCriar(void)
{
	char* Caminho;
	TPainelStatus* NovoPainel;
	
	NovoPainel = (TPainelStatus*)malloc(sizeof(TPainelStatus));
	if (NovoPainel == NULL)
		return NULL;
	
	NovoPainel->FaseID = 0;
	NovoPainel->MaxSangue = 0;
	NovoPainel->Sangue = 0;
	
	Caminho = ReceberRecDirCompleto(REC_GRAFICO, "coracao1.png");
	NovoPainel->CoracaoVermelho = al_load_bitmap(Caminho);
	free(Caminho);
	
	Caminho = ReceberRecDirCompleto(REC_GRAFICO, "coracao2.png");
	NovoPainel->CoracaoCinza = al_load_bitmap(Caminho);
	free(Caminho);
	
	Caminho = ReceberRecDirCompleto(REC_GRAFICO, "face.png");
	NovoPainel->Face = al_load_bitmap(Caminho);
	free(Caminho);	
	
	return NovoPainel;
}

void PainelStatusDestruir(TPainelStatus** PainelStatus)
{
	if ((*PainelStatus)->CoracaoVermelho != NULL)
		al_destroy_bitmap((*PainelStatus)->CoracaoVermelho);
	if ((*PainelStatus)->CoracaoCinza != NULL)
		al_destroy_bitmap((*PainelStatus)->CoracaoCinza);
	if ((*PainelStatus)->Face != NULL)
		al_destroy_bitmap((*PainelStatus)->Face);

	free(*PainelStatus);
	PainelStatus = NULL;
}

void PainelStatusExibir(TPainelStatus* PStatus)
{
	int i;
	int TopoPainel;
	int Largura;
	ALLEGRO_COLOR corBranca = al_map_rgb(110, 110, 110);
	ALLEGRO_COLOR corPreta = al_map_rgb(0, 0, 0);
	TPonto PontoDesenho;
	
	TopoPainel = TELA_ALTURA - 55;
	Largura = 180;
	al_draw_rectangle(0, TopoPainel, Largura, TELA_ALTURA, corBranca, 0);
	al_draw_filled_rectangle(1, TopoPainel + 2, Largura - 1, TELA_ALTURA - 1, corPreta);
	al_draw_line(5, TELA_ALTURA - 2, Largura - 5, TELA_ALTURA - 2, corBranca, 3);
	
	PontoDesenho.x = TopoPainel + 4;
	PontoDesenho.y = 4;	
	TelaDesenhar(PStatus->Face, &PontoDesenho);
	
	PontoDesenho.x = TopoPainel + 4 + 11;
	for (i = 0; i < PStatus->MaxSangue; i++)
	{
		PontoDesenho.y = 50 + i*22 + i*4;
		if (i < PStatus->Sangue)
			TelaDesenhar(PStatus->CoracaoVermelho, &PontoDesenho);
		else
			TelaDesenhar(PStatus->CoracaoCinza, &PontoDesenho);
	}
}