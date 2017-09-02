#ifndef _TIPOS_H_
#define _TIPOS_H_

#define FALSE 0
#define TRUE 1

#define TELA_ALTURA 600
#define TELA_LARGURA 800

#define MAX_VETORCHAR 33

typedef enum {tdBaixo, tdEsquerda, tdDireita, tdCima} TDirecao;

typedef struct {
	float x;
	float y;
} TPonto;

#endif
