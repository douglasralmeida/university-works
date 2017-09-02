#ifndef _AUDIO_H_
#define _AUDIO_H_

#include <allegro5/allegro_audio.h>

#define AUDIO_ALAKBAR 0

#define MELODIA_VENCER 0
#define MELODIA_PERDER 1
#define MELODIA_COMECAR 2

typedef struct 
{
	ALLEGRO_SAMPLE** Morte;
	ALLEGRO_SAMPLE* MusicaAmbiente;
	ALLEGRO_SAMPLE_ID MusicaAmbienteID;
	ALLEGRO_SAMPLE** Passadas;
	ALLEGRO_SAMPLE** Tiros;
	ALLEGRO_SAMPLE** Vozes;
	ALLEGRO_SAMPLE** Eventos;
	int EventosCont;
	int MorteCont;
	int PassadaCont;
	int TirosCont;
	int VozCont;
	int TocandoMelodia;
} TAudioBuffer;

TAudioBuffer* AudioBufferCriar(void);
void AudioBufferDestruir(TAudioBuffer** PBufferAudio);
void AudioBufferAdicEventos(TAudioBuffer* BufferAudio, int QuantEventos, char** ArquivosAudio);
void AudioBufferAdicMorte(TAudioBuffer* BufferAudio, int QuantMorte, char** ArquivosAudio);
void AudioBufferAdicTiros(TAudioBuffer* BufferAudio, int QuantTiros, char** ArquivosAudio);
void AudioBufferAdicPassada(TAudioBuffer* BufferAudio, int QuantPassadas, char** ArquivosAudio);
void AudioBufferAdicVozes(TAudioBuffer* BufferAudio, int QuantVozes, char** ArquivosAudio);
void AudioBufferPreparar(TAudioBuffer* BufferAudio);
void AudioBufferSetMusAmbiente(TAudioBuffer* BufferAudio, char* ArquivoAudio);
void PararMelodia(TAudioBuffer* BufferAudio);
void TocarSomUnicaVez(ALLEGRO_SAMPLE* Som);
void TocarMelodia(TAudioBuffer* BufferAudio);
void TocarSomEvento(TAudioBuffer* BufferAudio, int EventoID);
void TocarSomMorte(TAudioBuffer* BufferAudio, int MorteID);
void TocarSomPassada(TAudioBuffer* BufferAudio, int PassadaID);
void TocarSomTiro(TAudioBuffer* BufferAudio, int TiroID);
void TocarSomVoz(TAudioBuffer* BufferAudio, int VozID);

#endif