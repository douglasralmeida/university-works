#include <allegro5/allegro.h>
#include "funcoes.h"
#include "fonte.h"
#include "menu.h"
#include "janela.h"
#include "janelas.h"

#define TRUE 1
#define FALSE 0

int JanelaAbrir_Exibir(void)
{
	int Resultado;
	TJanela* Janela;
	int Teclas[6] = {ALLEGRO_KEY_UP, ALLEGRO_KEY_DOWN, ALLEGRO_KEY_RIGHT, ALLEGRO_KEY_LEFT, ALLEGRO_KEY_ESCAPE, ALLEGRO_KEY_ENTER};

	Janela = JanelaCriar();
	JanelaSetBitmap(Janela, "menu.png");
	JanelaSetRotulo(Janela, "ABRIR JOGO");
	JanelaMenuCriar(Janela, 7);
	JanelaMenuAdic(Janela, "(...)", mtSimples, NULL, NULL, jrNada);
	JanelaMenuAdic(Janela, "(...)", mtSimples, NULL, NULL, jrNada);
	JanelaMenuAdic(Janela, "(...)", mtSimples, NULL, NULL, jrNada);
	JanelaMenuAdic(Janela, "(...)", mtSimples, NULL, NULL, jrNada);
	JanelaMenuAdic(Janela, "(...)", mtSimples, NULL, NULL, jrNada);
	JanelaMenuAdic(Janela, "(...)", mtSimples, NULL, NULL, jrNada);	
	JanelaMenuAdic(Janela, "Desistir", mtSimples, NULL, NULL, jrCancelar);
	JanelaSetTeclas(Janela, 6, Teclas);
	Resultado = JanelaExibir(Janela);
	
	return Resultado;
}

void JanelaAjuda_Exibir(void)
{
	char* Naveg0 = "Objetivo";
	char* Naveg0txt = "Mate o terrorista chefao e va para a area de escape mais proxima!";
	char* Naveg1 = "Para navegar pelos menus:";
	char* Naveg1txt = "Utilize apenas as teclas direcionais, ENTER e ESC para nevegar pelos menus.";
	char* Naveg2 = "Para jogar:";
	char* Naveg2txt1 = "Para frente: W ou PARA CIMA.";
	char* Naveg2txt2 = "Para tras: S ou PARA BAIXO.";
	char* Naveg2txt3 = "Para esquerda: A ou PARA ESQUERDA.";
	char* Naveg2txt4 = "Para direita: D ou PARA DIREITA.";
	char* Naveg2txt5 = "Para mirar: Utilize o mouse.";
	char* Naveg2txt6 = "Para atirar: ESPACO ou BOTAO ESQUERDO do mouse.";
	char* Naveg2txt7 = "Para sair: ESC.";
	TJanela* Janela;
	int Teclas[6] = {ALLEGRO_KEY_UP, ALLEGRO_KEY_DOWN, ALLEGRO_KEY_RIGHT, ALLEGRO_KEY_LEFT, ALLEGRO_KEY_ESCAPE, ALLEGRO_KEY_ENTER};
	
	Janela = JanelaCriar();
	JanelaTextoCriar(Janela, 12);
	JanelaTextoAdic(Janela, Naveg0);
	JanelaTextoAdic(Janela, Naveg0txt);
	JanelaTextoAdic(Janela, Naveg1);
	JanelaTextoAdic(Janela, Naveg1txt);
	JanelaTextoAdic(Janela, Naveg2);
	JanelaTextoAdic(Janela, Naveg2txt1);
	JanelaTextoAdic(Janela, Naveg2txt2);
	JanelaTextoAdic(Janela, Naveg2txt3);
	JanelaTextoAdic(Janela, Naveg2txt4);
	JanelaTextoAdic(Janela, Naveg2txt5);
	JanelaTextoAdic(Janela, Naveg2txt6);
	JanelaTextoAdic(Janela, Naveg2txt7);
	JanelaSetBitmap(Janela, "menu.png");
	JanelaSetRotulo(Janela, "AJUDA DO JOGO");
	JanelaMenuCriar(Janela, 1);
	Janela->Menu->Altura = 480;
	JanelaMenuAdic(Janela, "Voltar", mtSimples, NULL, NULL, jrCancelar);
	JanelaSetTeclas(Janela, 6, Teclas);
	JanelaExibir(Janela);
}

int JanelaDificuldade_Exibir(int* Dificuldade)
{
	int Resultado;
	TJanela* Janela;
	int Teclas[6] = {ALLEGRO_KEY_UP, ALLEGRO_KEY_DOWN, ALLEGRO_KEY_RIGHT, ALLEGRO_KEY_LEFT, ALLEGRO_KEY_ESCAPE, ALLEGRO_KEY_ENTER};
	char* Opcoes[2] = {"Facil", "Dificil"};

	Janela = JanelaCriar();
	JanelaSetBitmap(Janela, "menu.png");
	JanelaSetRotulo(Janela, "NIVEL DE DIFICULDADE");

	JanelaMenuCriar(Janela, 3);
	JanelaMenuAdic(Janela, "Nivel", mtOpcao, (void*)Dificuldade, Opcoes, jrNada);

	JanelaMenuAdic(Janela, "Iniciar", mtSimples, NULL, NULL, jrOK);
	JanelaMenuAdic(Janela, "Voltar", mtSimples, NULL, NULL, jrCancelar);

	JanelaSetTeclas(Janela, 6, Teclas);
	Resultado = JanelaExibir(Janela);
	
	return Resultado;
}

int JanelaIniciar_Exibir(void)
{
	int Resultado;
	TJanela* Janela;
	int Teclas[6] = {ALLEGRO_KEY_UP, ALLEGRO_KEY_DOWN, ALLEGRO_KEY_RIGHT, ALLEGRO_KEY_LEFT, ALLEGRO_KEY_ESCAPE, ALLEGRO_KEY_ENTER};

	Janela = JanelaCriar();
	JanelaSetBitmap(Janela, "menu.png");
	JanelaSetRotulo(Janela, "DIGITE SEU NOME");

	//A
	JanelaMenuCriar(Janela, 2);
	Janela->Menu->Altura = 480;
	JanelaMenuAdic(Janela, "Continuar", mtSimples, NULL, NULL, jrOK);
	JanelaMenuAdic(Janela, "Voltar", mtSimples, NULL, NULL, jrCancelar);

	JanelaSetTeclas(Janela, 6, Teclas);
	Resultado = JanelaExibir(Janela);
	
	return Resultado;
}

int JanelaOpcoes_Exibir(int* TocarSom, int* TocarMusica)
{
	int Resultado;
	TJanela* Janela;
	int Teclas[6] = {ALLEGRO_KEY_UP, ALLEGRO_KEY_DOWN, ALLEGRO_KEY_RIGHT, ALLEGRO_KEY_LEFT, ALLEGRO_KEY_ESCAPE, ALLEGRO_KEY_ENTER};
	int AntesTocarMusica = *TocarMusica;
	int AntesTocarSom = *TocarSom;
	char* Opcoes[2] = {"Sim", "Nao"};
	
	Janela = JanelaCriar();
	JanelaSetBitmap(Janela, "menu.png");
	JanelaSetRotulo(Janela, "OPCOES");
	JanelaMenuCriar(Janela, 4);
	JanelaMenuAdic(Janela, "Musica ambiente", mtOpcao, (void*)&AntesTocarMusica, Opcoes, jrNada);
	JanelaMenuAdic(Janela, "Efeitos sonoros", mtOpcao, (void*)&AntesTocarSom, Opcoes, jrNada);
	JanelaMenuAdic(Janela, "Salvar e voltar", mtSimples, NULL, NULL, jrOK);
	JanelaMenuAdic(Janela, "Desistir", mtSimples, NULL, NULL, jrCancelar);
	JanelaSetTeclas(Janela, 6, Teclas);
	Resultado = JanelaExibir(Janela);
	if (Resultado == jrOK)
	{
		*TocarMusica = AntesTocarMusica;
		*TocarSom = AntesTocarSom;
	}
	
	return Resultado;
}

int JanelaPrincipal_Exibir(void)
{
	int Resultado;
	TJanela* Janela;
	int Teclas[6] = {ALLEGRO_KEY_UP, ALLEGRO_KEY_DOWN, ALLEGRO_KEY_RIGHT, ALLEGRO_KEY_LEFT, ALLEGRO_KEY_ESCAPE, ALLEGRO_KEY_ENTER};
	int CmdAbrir = CMD_ABRIRJOGO;
	int CmdIniciar = CMD_NOVOJOGO;
	int CmdOpcoes = CMD_OPCOES;
	int CmdAjuda = CMD_AJUDA;

	Janela = JanelaCriar();
	if (Janela == NULL)
		return FALSE;
	
	JanelaSetBitmap(Janela, "menu.png");
	JanelaMenuCriar(Janela, 5);
	JanelaMenuAdic(Janela, "Iniciar novo jogo", mtComando, (void*)&CmdIniciar, NULL, jrNada);
	JanelaMenuAdic(Janela, "Abrir jogo", mtComando, (void*)&CmdAbrir, NULL, jrNada);
	JanelaMenuAdic(Janela, "Opcoes", mtComando, (void*)&CmdOpcoes, NULL, jrNada);
	JanelaMenuAdic(Janela, "Ajuda", mtComando, (void*)&CmdAjuda, NULL, jrNada);
	JanelaMenuAdic(Janela, "Sair", mtSimples, NULL, NULL, jrCancelar);
	JanelaSetTeclas(Janela, 6, Teclas);
	Resultado = JanelaExibir(Janela);

	return Resultado;
}