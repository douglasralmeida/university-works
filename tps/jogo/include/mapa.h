#ifndef _MAPAS_H_
#define _MAPAS_H_

#include "tipos.h"
#include "graficos.h"
#include "colisoes.h"

typedef struct {
		int Superior;
		int Inferior;
		int Direita;
		int Esquerda;
		int SuperiorDireita;
		int SuperiorEsquerda;
		int InferiorDireita;
		int InferiorEsquerda;
} TMapaBordaInfo;

typedef struct {
	int AudioPassada;
	int BitmapMascara;
	int Colisao;
	int TemSangue;
} TMapaItem;

typedef struct {
	char** AudiosPassadas;
	TMapaBordaInfo Borda;
	TPonto* CursorFoco;
	char* CursorMouse;
	int MascaraAltura;
	int MascaraLargura;
	char** Mascaras;
	int MundoAltura;
	int MundoLargura;
	int ObjetosColisao;
	TPonto PontoVisao;
	int QuadraFinal;
	int QuantMascaras;
	int QuantPassadas;
	int TamEstruturaX;
	int TamEstruturaY;
	TMapaItem** Estrutura;
} TMapa;

TMapa* MapaCriar(void);
void MapaDestruir(TMapa** PMapa);
int MapaAbrir(TMapa* Mapa, char* ArquivoMapa);
int MapaAudioPassada(TMapa* Mapa, TPonto Ponto);
void MapaConstruir(TMapa* Mapa, TPonto Escape, TBitmapBuffer* Buffer);
int MapaContarObjInterativos(TMapa* Mapa);
void MapaDesenhar(TMapa* Mapa, TBitmapBuffer* Buffer);
void MapaMovimentar(TMapa* Mapa, TPonto* PontoFora);
int MapaLimite(TMapa* Mapa, int i, int j);
int MapaItemAbrir(TMapa* Mapa, int Quantidade, FILE* Arquivo);
#endif