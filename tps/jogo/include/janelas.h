#ifndef _JANELAS_H_
#define _JANELAS_H_

#define CMD_NOVOJOGO 2
#define CMD_ABRIRJOGO 3
#define CMD_OPCOES 4
#define CMD_AJUDA 5
#define CMD_SAIR 0

int JanelaAbrir_Exibir(void);
void JanelaAjuda_Exibir(void);
int JanelaDificuldade_Exibir(int* Dificuldade);
int JanelaIniciar_Exibir(void);
int JanelaOpcoes_Exibir(int* TocarSom, int* TocarMusica);
int JanelaPrincipal_Exibir(void);

#endif