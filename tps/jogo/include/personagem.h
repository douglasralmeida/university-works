#ifndef _PERSONAGEM_H_
#define _PERSONAGEM_H_

#include <allegro5/allegro.h>
#include "tipos.h"
#include "matematica.h"
#include "fisica.h"
#include "colisoes.h"

#define JOGADORID 1001
#define CHEFAOID 2001

typedef struct {
	unsigned int ID;
	int Altura;
	char* ArquivoPele;
	int Ativo;
	int DelayParaCaminhar;
	int DelayParaProcurar;
	int EstaVivo;
	int Largura;
	unsigned int MascaraID;
	char* Nome;
	TPonto PontoFrontal;
	TQuadra Posicao;
	int PosicaoPernas;
	float PosXAnterior;
	float PosYAnterior;
	int RecargaProjetil;
	int Saude;
	int TempoRecarga;
	int Transparencia;
	int TransparenciaCont;
	TVetor Trajetoria;
} TPersonagem;

typedef struct {
	TPersonagem* Chefao;
	TPersonagem* Jogador;
	TPersonagem* Inimigos;
	TPersonagem* Refens;
	int QuantInimigos;
	int QuantRefens;	
} TPersonagens;

TPersonagem* PersonagemCriar(void);
void PersonagemDestruir(TPersonagem** PPersonagem);
int PersonagemAbrir(TPersonagem* Personagem, char* ArquivoPerson);
void PersonagemAtingir(TPersonagem* Personagem);
void PersonagemAtivar(TPersonagem* Personagem, TAudioBuffer* BufferAudio);
void PersonagemAtualizar(TPersonagem* Personagem, TColisor* Colisor);
void PersonagemConfigAngulo(TPersonagem* Personagem, float DirecaoX, float DirecaoY, TPonto* PontoVisao);
void PersonagemDesenhar(TPersonagem* Personagem, int PersonagemTipo, TBitmapBuffer* Buffer, TPonto* PontoVisao);
void PersonagemMatar(TPersonagem* Personagem);
int PersonagemMovimentar(TPersonagem* Personagem, ALLEGRO_KEYBOARD_STATE* AlEstadoTecla);
void PersonagemPosicionar(TPersonagem* Personagem, TPonto NovaPosicao);
int PersonagemProcurarJogador(TPersonagem* Personagem, TQuadra* JogadorQuadra, TPonto* PontoVisao);
void PersonagemRecarregarProjetil(TPersonagem* Personagem);
void PersonagemRotacionar(TPersonagem* Personagem);
int PersonagemVisivel(TPersonagem* Personagem, TPonto* PontoVisao);

TPersonagem* PersonagemPorMascara(TPersonagens* Personagens, unsigned int MascaraID);

#endif