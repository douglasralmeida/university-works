#include <stdio.h>
#include <allegro5/allegro.h>
#include "funcoes.h"
#include "audio.h"

TAudioBuffer* AudioBufferCriar(void)
{
	TAudioBuffer* NovoBufferAudio;
	NovoBufferAudio = (TAudioBuffer*)malloc(sizeof(TAudioBuffer));
	NovoBufferAudio->Eventos = NULL;
	NovoBufferAudio->EventosCont = 0;
	NovoBufferAudio->Morte = NULL;
	NovoBufferAudio->MorteCont = 0;
	NovoBufferAudio->MusicaAmbiente = NULL;
	NovoBufferAudio->Passadas = NULL;
	NovoBufferAudio->PassadaCont = 0;
	NovoBufferAudio->Tiros = NULL;
	NovoBufferAudio->TirosCont = 0;
	NovoBufferAudio->Vozes = NULL;
	NovoBufferAudio->VozCont = 0;
	NovoBufferAudio->TocandoMelodia = FALSE;
	
	return NovoBufferAudio;
}

void AudioBufferDestruir(TAudioBuffer** PBufferAudio)
{
	int i;

	if ((*PBufferAudio)->Eventos != NULL)
	{
		for (i=0; i < (*PBufferAudio)->EventosCont; i++)
		{
			al_destroy_sample((*PBufferAudio)->Eventos[i]);
		}
		free((*PBufferAudio)->Eventos);
	}	
	if ((*PBufferAudio)->Morte != NULL)
	{
		for (i=0; i < (*PBufferAudio)->MorteCont; i++)
		{
			al_destroy_sample((*PBufferAudio)->Morte[i]);
		}
		free((*PBufferAudio)->Morte);
	}
	if ((*PBufferAudio)->Passadas != NULL)
	{
		for (i=0; i < (*PBufferAudio)->PassadaCont; i++)
		{
			al_destroy_sample((*PBufferAudio)->Passadas[i]);
		}
		free((*PBufferAudio)->Passadas);
	}
	if ((*PBufferAudio)->Tiros != NULL)
	{
		for (i=0; i < (*PBufferAudio)->TirosCont; i++)
		{
			al_destroy_sample((*PBufferAudio)->Tiros[i]);
		}
		free((*PBufferAudio)->Tiros);
	}
	if ((*PBufferAudio)->Vozes != NULL)
	{
		for (i=0; i < (*PBufferAudio)->VozCont; i++)
		{
			al_destroy_sample((*PBufferAudio)->Vozes[i]);
		}
		free((*PBufferAudio)->Vozes);
	}
	al_destroy_sample((*PBufferAudio)->MusicaAmbiente);
	free(*PBufferAudio);
	*PBufferAudio = NULL;
}

void AudioBufferAdicEventos(TAudioBuffer* BufferAudio, int QuantEventos, char** ArquivosAudio)
{
	int i;
	char* Caminho;

	BufferAudio->Eventos = (ALLEGRO_SAMPLE**)malloc(sizeof(ALLEGRO_SAMPLE*)*QuantEventos);
	for (i = 0; i < QuantEventos; i++)
	{
		Caminho = ReceberRecDirCompleto(REC_SOM, ArquivosAudio[i]);
		BufferAudio->Eventos[i] = al_load_sample(Caminho);
		BufferAudio->EventosCont++;
		free(Caminho);
	}	
}

void AudioBufferAdicMorte(TAudioBuffer* BufferAudio, int QuantMorte, char** ArquivosAudio)
{
	int i;
	char* Caminho;

	BufferAudio->Morte = (ALLEGRO_SAMPLE**)malloc(sizeof(ALLEGRO_SAMPLE*)*QuantMorte);
	for (i = 0; i < QuantMorte; i++)
	{
		Caminho = ReceberRecDirCompleto(REC_SOM, ArquivosAudio[i]);
		BufferAudio->Morte[i] = al_load_sample(Caminho);
		BufferAudio->MorteCont++;
		free(Caminho);
	}	
}

void AudioBufferAdicPassada(TAudioBuffer* BufferAudio, int QuantPassadas, char** ArquivosAudio)
{
	int i;
	char* Caminho;

	BufferAudio->Passadas = (ALLEGRO_SAMPLE**)malloc(sizeof(ALLEGRO_SAMPLE*)*QuantPassadas);
	for (i = 0; i < QuantPassadas; i++)
	{
		Caminho = ReceberRecDirCompleto(REC_SOM, ArquivosAudio[i]);
		BufferAudio->Passadas[i] = al_load_sample(Caminho);
		BufferAudio->PassadaCont++;
		free(Caminho);
	}
}

void AudioBufferAdicTiros(TAudioBuffer* BufferAudio, int QuantTiros, char** ArquivosAudio)
{
	int i;
	char* Caminho;

	BufferAudio->Tiros = (ALLEGRO_SAMPLE**)malloc(sizeof(ALLEGRO_SAMPLE*)*QuantTiros);
	for (i = 0; i < QuantTiros; i++)
	{
		Caminho = ReceberRecDirCompleto(REC_SOM, ArquivosAudio[i]);
		BufferAudio->Tiros[i] = al_load_sample(Caminho);
		BufferAudio->TirosCont++;
		free(Caminho);
	}	
}

void AudioBufferAdicVozes(TAudioBuffer* BufferAudio, int QuantVozes, char** ArquivosAudio)
{
	int i;
	char* Caminho;

	BufferAudio->Vozes = (ALLEGRO_SAMPLE**)malloc(sizeof(ALLEGRO_SAMPLE*)*QuantVozes);
	for (i = 0; i < QuantVozes; i++)
	{
		Caminho = ReceberRecDirCompleto(REC_SOM, ArquivosAudio[i]);
		BufferAudio->Vozes[i] = al_load_sample(Caminho);
		BufferAudio->VozCont++;
		free(Caminho);
	}
}

void AudioBufferPreparar(TAudioBuffer* BufferAudio)
{
	int Total;
	Total = BufferAudio->EventosCont + BufferAudio->PassadaCont + BufferAudio->MorteCont + BufferAudio->TirosCont + BufferAudio->VozCont + 1;
	if (BufferAudio->MusicaAmbiente != NULL)
		Total++;
	if (Total > 0)
		al_reserve_samples(Total);
}

void AudioBufferSetMusAmbiente(TAudioBuffer* BufferAudio, char* ArquivoAudio)
{
	char* Caminho;

	Caminho = ReceberRecDirCompleto(REC_MELODIA, ArquivoAudio);
	BufferAudio->MusicaAmbiente = al_load_sample(Caminho);
	free(Caminho);
}

void TocarSomUnicaVez(ALLEGRO_SAMPLE* Som)
{
	if (Application.Config.TocarSom)
		al_play_sample(Som, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
}

void PararMelodia(TAudioBuffer* BufferAudio)
{
	if (BufferAudio->TocandoMelodia)
	{
		al_stop_sample(&BufferAudio->MusicaAmbienteID);
		BufferAudio->TocandoMelodia = FALSE;
	}
}

void TocarMelodia(TAudioBuffer* BufferAudio)
{
	if (BufferAudio->TocandoMelodia == TRUE)
		PararMelodia(BufferAudio);
	if (Application.Config.TocarMusica)
	{
		al_play_sample(BufferAudio->MusicaAmbiente, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, &BufferAudio->MusicaAmbienteID);
		BufferAudio->TocandoMelodia = TRUE;
	}
}

void TocarSomEvento(TAudioBuffer* BufferAudio, int EventoID)
{
	TocarSomUnicaVez(BufferAudio->Eventos[EventoID]);
}

void TocarSomMorte(TAudioBuffer* BufferAudio, int MorteID)
{
	TocarSomUnicaVez(BufferAudio->Morte[MorteID]);
}

void TocarSomPassada(TAudioBuffer* BufferAudio, int PassadaID)
{
	TocarSomUnicaVez(BufferAudio->Passadas[PassadaID]);
}

void TocarSomTiro(TAudioBuffer* BufferAudio, int TiroID)
{
	TocarSomUnicaVez(BufferAudio->Tiros[TiroID]);
}

void TocarSomVoz(TAudioBuffer* BufferAudio, int VozID)
{
	TocarSomUnicaVez(BufferAudio->Vozes[VozID]);
}