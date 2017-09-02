#ifndef _JOGO_H_	
#define _JOGO_H_

#include "colisoes.h"
#include "audio.h"
#include "fonte.h"
#include "graficos.h"
#include "painelstatus.h"
#include "personagem.h"
#include "projetil.h"
#include "mapa.h"
#include "fase.h"

typedef enum {moFacil, moDificil} TJogoModo;

typedef struct {
	TAudioBuffer* BufferAudio;
	TBitmapBuffer* BufferBitmaps;
	TFonteBuffer* BufferFontes;
	char* CursorMouse;
	TColisor* DetectorColisoes;
	TFase* FaseAtual;
	int FaseAtualID;
	char** Fases;
	float FPS;
	TMapa* MapaAtual;
	int MaxParticulas;
	int MaxProjetis;
	TJogoModo Modo;
	TPainelStatus* PainelStatus;
	TPersonagens* Personagens;
	TProjetil** Projetis;
	int ProjetisCont;
	TQuadra QuadraVitoria;
	int QuantFases;
} TJogo;

TJogo* JogoCriar(TJogoModo Modo);
void JogoDestruir(TJogo** Jogo);
int JogoAbrir(TJogo* Jogo);
int JogoCarregarFase(TJogo* Jogo);
int JogoCarregarMapa(TJogo* Jogo);
int JogoCarregarPersonagens(TJogo* Jogo);
int JogoChecarDados(TJogo* Jogo);
int JogoControlar(TJogo* Jogo);
void JogoDesenhar(TJogo* Jogo);
void JogoExibirStatus(TJogo* Jogo);
void JogoFaseIniciar(TJogo* Jogo);
int JogoIniciar(TJogo* Jogo);
void JogoLimpar(TJogo* Jogo);
int JogoMovimentar(TJogo* Jogo, ALLEGRO_KEYBOARD_STATE* AlEstadoTecla, ALLEGRO_MOUSE_STATE* AlEstadoMouse);
TPersonagens* JogoPersonagensCriar(TFase* Fase);
void JogoPerdeu(TJogo* Jogo);
void JogoPersonagensDestruir(TPersonagens** Personagens);
void JogoPersonagensAtirar(TJogo* Jogo);
void JogoPersonagensRecarregarProjetil(TJogo* Jogo);
int JogoPausa(TJogo* Jogo);
int JogoPrepararBuffers(TJogo* Jogo);
int JogoPrepararDetectorColisoes(TJogo* Jogo);
int JogoPrepararVetores(TJogo* Jogo);
void JogoTelaReposicionar(TJogo* Jogo);
void JogoVenceu(TJogo* Jogo);
void JogadorAtirar(TJogo* Jogo, TPersonagem* Jogador);

void ProjetisDesenhar(TJogo* Jogo);
void ProjetisMovimentar(TJogo* Jogo);

#endif
