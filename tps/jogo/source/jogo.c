#include "tipos.h"
#include "matematica.h"
#include "fisica.h"
#include "funcoes.h"
#include "vetor.h"
#include "arquivo.h"
#include "teclado.h"
#include "mouse.h"
#include "fonte.h"
#include "jogo.h"

TJogo* JogoCriar(TJogoModo Modo)
{
	TJogo* NovoJogo;

	NovoJogo = (TJogo*)malloc(sizeof(TJogo));
	NovoJogo->BufferAudio = NULL;
	NovoJogo->BufferBitmaps = NULL;
	NovoJogo->BufferFontes = NULL;
	NovoJogo->CursorMouse = NULL;
	NovoJogo->DetectorColisoes = NULL;
	NovoJogo->FaseAtual = NULL;
	NovoJogo->FaseAtualID = 0;
	NovoJogo->Fases = NULL;
	NovoJogo->FPS = 60.0;
	NovoJogo->MapaAtual = NULL;
	NovoJogo->MaxParticulas = 0;
	NovoJogo->MaxProjetis = 0;
	NovoJogo->Modo = Modo;
	NovoJogo->PainelStatus = PainelStatusCriar();
	NovoJogo->Personagens = NULL;
	NovoJogo->Projetis = NULL;
	NovoJogo->ProjetisCont = 0;
	NovoJogo->QuadraVitoria.PontoInicial.x = 0;
	NovoJogo->QuadraVitoria.PontoInicial.y = 0;
	NovoJogo->QuadraVitoria.PontoFinal.x = 0;
	NovoJogo->QuadraVitoria.PontoFinal.y = 0;
	NovoJogo->QuantFases = 0;
	if (Modo == moFacil)
	{
		NovoJogo->PainelStatus->MaxSangue = 5;
	}
	else if (Modo == moDificil)
	{
		NovoJogo->PainelStatus->MaxSangue = 3;		
	}	
	
	return NovoJogo;	
}

void JogoDestruir(TJogo** PJogo)
{
	if ((*PJogo)->CursorMouse != NULL)
		free((*PJogo)->CursorMouse);
	if ((*PJogo)->DetectorColisoes != NULL)
		ColisorDestruir(&(*PJogo)->DetectorColisoes);
	if ((*PJogo)->PainelStatus != NULL)
		PainelStatusDestruir(&(*PJogo)->PainelStatus);
	if ((*PJogo)->FaseAtual != NULL)
		FaseDestruir(&(*PJogo)->FaseAtual);
	if ((*PJogo)->Fases != NULL)
		MatrizDestruir((void***)&(*PJogo)->Fases, (*PJogo)->QuantFases);
	if ((*PJogo)->MapaAtual != NULL)
		MapaDestruir(&(*PJogo)->MapaAtual);
	if ((*PJogo)->Personagens != NULL)
		JogoPersonagensDestruir(&(*PJogo)->Personagens);
	if ((*PJogo)->Projetis != NULL)
		MatrizDestruir((void***)&(*PJogo)->Projetis, (*PJogo)->MaxProjetis);

	free(*PJogo);
	*PJogo = NULL;
}

int JogoAbrir(TJogo* Jogo)
{
	int TempInt;
	char* ArquivoScript = "recursos\\jogo.dados";
	FILE* Arquivo;

	Arquivo = fopen(ArquivoScript, "rt");
	if (Arquivo != NULL)
	{
		if (!SecaoChecar(":ARQUIVOJOGO", Arquivo))
		{
			ArquivoFechar(Arquivo);
			return FALSE;
		}		
		if (LerPropriedadeInteiro("Versao", &TempInt, Arquivo))
		{
			if (TempInt != 1)
			{
				ArquivoFechar(Arquivo);
				return FALSE;
			}
		}
		else
		{
			ArquivoFechar(Arquivo);
			return FALSE;
		}

		if (!SecaoChecar(":DEFINICOES", Arquivo))
		{
			ArquivoFechar(Arquivo);
			return FALSE;
		}
		Jogo->CursorMouse = CVetorCriar(MAX_VETORCHAR);
		if (Jogo->CursorMouse == NULL)
		{
			ArquivoFechar(Arquivo);
			return FALSE;
		}
		if (!LerPropriedadeString("CursorMouse", Jogo->CursorMouse, Arquivo))
		{
			ArquivoFechar(Arquivo);
			return FALSE;
		}
		if (!LerPropriedadeInteiro("MaxParticulas", &Jogo->MaxParticulas, Arquivo))
		{
			ArquivoFechar(Arquivo);
			return FALSE;
		}
		if (!LerPropriedadeInteiro("MaxProjetis", &Jogo->MaxProjetis, Arquivo))
		{
			ArquivoFechar(Arquivo);
			return FALSE;
		}		
		if (!LerPropriedadeInteiro("QuantidadeFases", &Jogo->QuantFases, Arquivo))
		{
			ArquivoFechar(Arquivo);
			return FALSE;
		}

		if (!SecaoChecar(":FASES", Arquivo))
		{
			ArquivoFechar(Arquivo);
			return FALSE;
		}
		Jogo->Fases = CMatrizCriar(Jogo->QuantFases, MAX_VETORCHAR);
		if (!LerVetorStr(Jogo->Fases, Jogo->QuantFases, Arquivo))
		{
			ArquivoFechar(Arquivo);
			return FALSE;
		}
		
		ArquivoFechar(Arquivo);
		return TRUE;
	}
	else
		return FALSE;
}

int JogoCarregarFase(TJogo* Jogo)
{
	Jogo->FaseAtual = FaseCriar();
	if (Jogo->FaseAtual == NULL)
		return FALSE;
	if (!FaseAbrir(Jogo->FaseAtual, Jogo->Fases[Jogo->FaseAtualID]))
	{
		FaseDestruir(&Jogo->FaseAtual);
		return FALSE;
	}
	Jogo->FaseAtualID++;
	Jogo->QuadraVitoria.PontoInicial.x = Jogo->FaseAtual->PosicaoFinal.x;
	Jogo->QuadraVitoria.PontoInicial.y = Jogo->FaseAtual->PosicaoFinal.y;
	Jogo->QuadraVitoria.PontoFinal.x = Jogo->FaseAtual->PosicaoFinal.x + 32;
	Jogo->QuadraVitoria.PontoFinal.y = Jogo->FaseAtual->PosicaoFinal.y + 32;

	return TRUE;
}

int JogoCarregarMapa(TJogo* Jogo)
{
	int i; 
	int j;
	int MascID;
	
	Jogo->MapaAtual = MapaCriar();
	if (Jogo->MapaAtual == NULL)
		return FALSE;
	if (!MapaAbrir(Jogo->MapaAtual, Jogo->FaseAtual->ArquivoMapa))
	{
		MapaDestruir(&Jogo->MapaAtual);
		return FALSE;
	}
	
	for (i = 0; i < Jogo->MapaAtual->TamEstruturaY; i++)
		for (j = 0; j < Jogo->MapaAtual->TamEstruturaX; j++)
			if ((MapaLimite(Jogo->MapaAtual, i, j)) ||
				(Jogo->MapaAtual->Estrutura[i][j].Colisao == TRUE))
			{
				MascID = ColisorMascaraAdic(Jogo->DetectorColisoes, 4);
				Jogo->DetectorColisoes->Mascaras[MascID].Vertices[0].x = j * Jogo->MapaAtual->MascaraLargura;
				Jogo->DetectorColisoes->Mascaras[MascID].Vertices[0].y = i * Jogo->MapaAtual->MascaraAltura;
				Jogo->DetectorColisoes->Mascaras[MascID].Vertices[1].x = (j + 1) * Jogo->MapaAtual->MascaraLargura;
				Jogo->DetectorColisoes->Mascaras[MascID].Vertices[1].y = i * Jogo->MapaAtual->MascaraAltura;
				Jogo->DetectorColisoes->Mascaras[MascID].Vertices[2].x = j * Jogo->MapaAtual->MascaraLargura;
				Jogo->DetectorColisoes->Mascaras[MascID].Vertices[2].y = (i + 1) * Jogo->MapaAtual->MascaraAltura;
				Jogo->DetectorColisoes->Mascaras[MascID].Vertices[3].x = (j + 1) * Jogo->MapaAtual->MascaraLargura;
				Jogo->DetectorColisoes->Mascaras[MascID].Vertices[3].y = (i + 1) * Jogo->MapaAtual->MascaraAltura;
			}

	return TRUE;
}

int JogoCarregarPersonagens(TJogo* Jogo)
{
	int i;
	
	//cria os personagens
	Jogo->Personagens = JogoPersonagensCriar(Jogo->FaseAtual);
	//adiciona o jogador no detector de colisoes
	Jogo->Personagens->Jogador->MascaraID = ColisorMascaraAdic(Jogo->DetectorColisoes, 4);
	PersonagemAtualizar(Jogo->Personagens->Jogador, Jogo->DetectorColisoes);
	//adiciona o chefao no detector de colisoes
	Jogo->Personagens->Chefao->MascaraID = ColisorMascaraAdic(Jogo->DetectorColisoes, 4);
	PersonagemAtualizar(Jogo->Personagens->Chefao, Jogo->DetectorColisoes);
	//adiciona os inimigos no detectos de colisoes
	for (i = 0; i < Jogo->Personagens->QuantInimigos; i++)
	{
		Jogo->Personagens->Inimigos[i].MascaraID = ColisorMascaraAdic(Jogo->DetectorColisoes, 4);
		PersonagemAtualizar(&Jogo->Personagens->Inimigos[i], Jogo->DetectorColisoes);
	}

	if (Jogo->Modo == moFacil)
	{
		Jogo->Personagens->Jogador->Saude = 5;		
		Jogo->Personagens->Jogador->TempoRecarga = 60;
		for (i = 0; i < Jogo->Personagens->QuantInimigos; i++)
		{
			Jogo->Personagens->Inimigos[i].TempoRecarga = 80;
			Jogo->Personagens->Inimigos[i].Saude = 2;
		}
			Jogo->Personagens->Chefao->TempoRecarga = 70;
			Jogo->Personagens->Chefao->Saude = 3;
	}
	else
	{
		Jogo->Personagens->Jogador->Saude = 3;
		Jogo->Personagens->Jogador->TempoRecarga = 60;
		for (i = 0; i < Jogo->Personagens->QuantInimigos; i++)
		{
			Jogo->Personagens->Inimigos[i].TempoRecarga = 70;
			Jogo->Personagens->Inimigos[i].Saude = 3;
		}
		Jogo->Personagens->Chefao->TempoRecarga = 60;
		Jogo->Personagens->Chefao->Saude = 4;	
	}
	return (Jogo->Personagens != NULL);
}

int JogoChecarDados(TJogo* Jogo)
{
	if (Jogo->MaxParticulas < Jogo->MaxProjetis + Jogo->Personagens->QuantRefens + Jogo->Personagens->QuantInimigos + MapaContarObjInterativos(Jogo->MapaAtual) + 2) //2 = jogador e chefao 
	{
		ErroSimples(L"A quantidade de particulas suportada eh menor que a quantidade de objetos no jogo.");
		return FALSE;
	}
	
	return TRUE;
}

int JogoControlar(TJogo* Jogo)
{
	float MouseX = 0.0;
	float MouseY = 0.0;
	int controlarjogo = TRUE;
	int podedesenhar = TRUE;
	int jogadorvenceu = FALSE;
	ALLEGRO_TIMER* AlTimer = al_create_timer(1.0 / Jogo->FPS);
	ALLEGRO_EVENT_QUEUE* AlFilaEventos = al_create_event_queue();
	ALLEGRO_KEYBOARD_STATE AlEstadoTecla;
	ALLEGRO_MOUSE_STATE AlEstadoMouse;
	ALLEGRO_EVENT AlEvento;
	
	TocarMelodia(Jogo->BufferAudio);
	al_register_event_source(AlFilaEventos, al_get_timer_event_source(AlTimer));
	al_register_event_source(AlFilaEventos, al_get_display_event_source(Application.Screen));
	al_register_event_source(AlFilaEventos, al_get_keyboard_event_source());
	al_register_event_source(AlFilaEventos, al_get_mouse_event_source());
	al_start_timer(AlTimer);
	JogoDesenhar(Jogo);
	PersonagemAtivar(Jogo->Personagens->Jogador, Jogo->BufferAudio);
	while (controlarjogo)
	{		
		al_wait_for_event(AlFilaEventos, &AlEvento);
		//al_get_next_event(AlFilaEventos, &AlEvento);
		al_get_keyboard_state(&AlEstadoTecla);
		al_get_mouse_state(&AlEstadoMouse);
		podedesenhar = FALSE;
		//Checa a area de escape para a vitoria
		if (Jogo->Personagens->Chefao->EstaVivo == FALSE)
			if (ExisteSobreposicaoQuadras(&Jogo->QuadraVitoria, &Jogo->Personagens->Jogador->Posicao))
			{
				JogoVenceu(Jogo);
				jogadorvenceu = TRUE;
				controlarjogo = FALSE;
			}
		//Checa a saude para a derrota
		if (Jogo->Personagens->Jogador->Saude <= 0)
		{
			JogoPerdeu(Jogo);
			controlarjogo = FALSE;
		}
		if (AlEvento.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		{
			controlarjogo = FALSE;
		}
		else if (AlEvento.type == ALLEGRO_EVENT_TIMER)
		{
			if (controlarjogo == TRUE)
			{
				if ((MouseX != AlEstadoMouse.x) || (MouseY != AlEstadoMouse.y))
				{
					MouseX = AlEstadoMouse.x;
					MouseY = AlEstadoMouse.y;
					PersonagemConfigAngulo(Jogo->Personagens->Jogador, MouseX, MouseY, &Jogo->MapaAtual->PontoVisao);
				}
				JogoMovimentar(Jogo, &AlEstadoTecla, &AlEstadoMouse);
				if (Application.ClosingAll == TRUE)
					controlarjogo = FALSE;
				else
					podedesenhar = TRUE;
			}
		}
		if (podedesenhar)
		{
			JogoDesenhar(Jogo);
		}
	}
	PararMelodia(Jogo->BufferAudio);
	al_destroy_event_queue(AlFilaEventos);
	al_destroy_timer(AlTimer);
	
	return jogadorvenceu;
}

void JogoDesenhar(TJogo* Jogo)
{
	int i;
	TCor corPreta;
	
	corPreta.EscalaVermelho = 0;
	corPreta.EscalaVerde = 0;
	corPreta.EscalaAzul = 0;
	TelaColorir(corPreta);

	MapaDesenhar(Jogo->MapaAtual, Jogo->BufferBitmaps);
	PersonagemDesenhar(Jogo->Personagens->Jogador, 0, Jogo->BufferBitmaps, &Jogo->MapaAtual->PontoVisao);
	if (PersonagemVisivel(Jogo->Personagens->Chefao, &Jogo->MapaAtual->PontoVisao))
		PersonagemDesenhar(Jogo->Personagens->Chefao, 1, Jogo->BufferBitmaps, &Jogo->MapaAtual->PontoVisao);
	for (i = 0; i < Jogo->Personagens->QuantInimigos; i++)
		if (PersonagemVisivel(&Jogo->Personagens->Inimigos[i], &Jogo->MapaAtual->PontoVisao))
			PersonagemDesenhar(&Jogo->Personagens->Inimigos[i], 2, Jogo->BufferBitmaps, &Jogo->MapaAtual->PontoVisao);
	for (i = 0; i < Jogo->Personagens->QuantRefens; i++)
		if (PersonagemVisivel(&Jogo->Personagens->Refens[i], &Jogo->MapaAtual->PontoVisao))
			PersonagemDesenhar(&Jogo->Personagens->Refens[i], 3, Jogo->BufferBitmaps, &Jogo->MapaAtual->PontoVisao);

	//Desenha projetis
	if (Jogo->ProjetisCont > 0)
	{
		ProjetisDesenhar(Jogo);
	}
	if (Application.DebugMode == TRUE)
		MascarasDesenhar(Jogo->DetectorColisoes, &Jogo->MapaAtual->PontoVisao);
	JogoExibirStatus(Jogo);
	TelaAtualizar();
}

void JogoExibirStatus(TJogo* Jogo)
{
	Jogo->PainelStatus->Sangue = Jogo->Personagens->Jogador->Saude;
	PainelStatusExibir(Jogo->PainelStatus);
}

int JogoIniciar(TJogo* Jogo)
{
	if (JogoPrepararDetectorColisoes(Jogo) == FALSE)
		return FALSE;
	
	if (JogoCarregarFase(Jogo))
	{
		if (JogoCarregarMapa(Jogo))
		{
			if (JogoCarregarPersonagens(Jogo))
			{
				if (JogoPrepararVetores(Jogo) == FALSE)
					return FALSE;
				if (JogoPrepararBuffers(Jogo) == FALSE)
					return FALSE;
					
				FaseIniciar(Jogo->FaseAtual);
				ConfigMouseCursor(Jogo->BufferBitmaps->Cursores[CUR_ALVO]);
				TocarSomUnicaVez(Jogo->BufferAudio->Eventos[MELODIA_COMECAR]);
				al_rest(8.0);
	
				return TRUE;
			}
			else
			{
				MapaDestruir(&Jogo->MapaAtual);
				FaseDestruir(&Jogo->FaseAtual);

				return FALSE;				
			}
		}
		else
		{
			FaseDestruir(&Jogo->FaseAtual);

			return FALSE;
		}
	}
	else
		return FALSE;
}

void JogoLimpar(TJogo* Jogo)
{
	AudioBufferDestruir(&Jogo->BufferAudio);
	BitmapBufferDestruir(&Jogo->BufferBitmaps);
	FonteBufferDestruir(&Jogo->BufferFontes);

	if (Jogo->DetectorColisoes != NULL)
		ColisorDestruir(&Jogo->DetectorColisoes);
	if (Jogo->Projetis != NULL)
	{
		MatrizDestruir((void***)&Jogo->Projetis, Jogo->MaxProjetis);
		Jogo->Projetis = NULL;
	}
	if (Jogo->Personagens != NULL)
		JogoPersonagensDestruir(&Jogo->Personagens);
	if (Jogo->MapaAtual != NULL)
		MapaDestruir(&Jogo->MapaAtual);
	if (Jogo->FaseAtual != NULL)
		FaseDestruir(&Jogo->FaseAtual);		
}

int JogoMovimentar(TJogo* Jogo, ALLEGRO_KEYBOARD_STATE* AlEstadoTecla, ALLEGRO_MOUSE_STATE* AlEstadoMouse)
{
	int i;
	int PassadaID;
	int houve_movimento = FALSE;
	int jogadorativo = FALSE;
	TPersonagem* Ativo;
	TPonto PontoJogadorTemp;
	
	//Recarregar armas
	JogoPersonagensRecarregarProjetil(Jogo);	
	//Pausa o Jogo
	if (al_key_down(AlEstadoTecla, ALLEGRO_KEY_ESCAPE))
	{
		JogoPausa(Jogo);
		return TRUE;
	}
	//Atira
	else if (al_key_down(AlEstadoTecla, ALLEGRO_KEY_SPACE) ||
			(AlEstadoMouse->buttons & 1))//botao esquerdo do mouse pressionado
		if (Jogo->Personagens->Jogador->RecargaProjetil >= Jogo->Personagens->Jogador->TempoRecarga)
		{
			JogadorAtirar(Jogo, Jogo->Personagens->Jogador);
			TocarSomTiro(Jogo->BufferAudio, 0);
		}
	//Movimenta o jogador
	PontoJogadorTemp.x = Jogo->Personagens->Jogador->PosXAnterior;
	PontoJogadorTemp.y = Jogo->Personagens->Jogador->PosYAnterior;

	Jogo->Personagens->Jogador->PosXAnterior = Jogo->Personagens->Jogador->Posicao.PontoInicial.x;
	Jogo->Personagens->Jogador->PosYAnterior = Jogo->Personagens->Jogador->Posicao.PontoInicial.y;
		
	jogadorativo = PersonagemMovimentar(Jogo->Personagens->Jogador, AlEstadoTecla);
	PersonagemAtualizar(Jogo->Personagens->Jogador, Jogo->DetectorColisoes);
	//Checa a existencia de colisoes
	if (jogadorativo)
	{
		if (HaColisaoObjetos(Jogo->DetectorColisoes, Jogo->Personagens->Jogador->MascaraID) >= 0)
		{
			PersonagemPosicionar(Jogo->Personagens->Jogador, PontoJogadorTemp);
			PersonagemAtualizar(Jogo->Personagens->Jogador, Jogo->DetectorColisoes);

			Jogo->Personagens->Jogador->PosXAnterior = PontoJogadorTemp.x;
			Jogo->Personagens->Jogador->PosYAnterior = PontoJogadorTemp.y;
		}
		else
		{
			PassadaID = MapaAudioPassada(Jogo->MapaAtual, Jogo->Personagens->Jogador->Posicao.PontoInicial);
			Jogo->Personagens->Jogador->DelayParaCaminhar++;
			if (Jogo->Personagens->Jogador->DelayParaCaminhar >= 26)
			{
				TocarSomPassada(Jogo->BufferAudio, PassadaID);
				Jogo->Personagens->Jogador->DelayParaCaminhar = 0;
			}
			houve_movimento = TRUE;
		}
	}
	//Movimenta os projetis
	if (Jogo->ProjetisCont > 0)
	{
		ProjetisMovimentar(Jogo);
		houve_movimento = TRUE;
	}
	//Movimenta o mapa
	if (jogadorativo)
	{
		JogoTelaReposicionar(Jogo);
		houve_movimento = TRUE;
	}
	//Movimenta os inimigos
	for (i = 0; i < Jogo->Personagens->QuantInimigos; i++)
	{
		Ativo = &Jogo->Personagens->Inimigos[i];
		if (PersonagemVisivel(Ativo, &Jogo->MapaAtual->PontoVisao))
			if (Ativo->EstaVivo == TRUE)
			{
				if (PersonagemProcurarJogador(Ativo, &Jogo->Personagens->Jogador->Posicao, &Jogo->MapaAtual->PontoVisao))
				{
					houve_movimento = TRUE;
					if (Ativo->Ativo == FALSE)
						PersonagemAtivar(Ativo, Jogo->BufferAudio);
				}
			}
	}
	//Movimenta o chefao
	if (PersonagemVisivel(Jogo->Personagens->Chefao, &Jogo->MapaAtual->PontoVisao))
		if (Jogo->Personagens->Chefao->EstaVivo == TRUE)
			{
				if (PersonagemProcurarJogador(Jogo->Personagens->Chefao, &Jogo->Personagens->Jogador->Posicao, &Jogo->MapaAtual->PontoVisao))
				{
					houve_movimento = TRUE;
					if (Jogo->Personagens->Chefao->Ativo == FALSE)
						PersonagemAtivar(Jogo->Personagens->Chefao, Jogo->BufferAudio);
				}
			}
	
	//Inimigo atira
	JogoPersonagensAtirar(Jogo);
	
	return houve_movimento;
}

TPersonagens* JogoPersonagensCriar(TFase* Fase)
{
	int i;
	TPersonagens* ListaPersonagens;
	TPonto PosicaoPersonagem;
	
	ListaPersonagens = (TPersonagens*)malloc(sizeof(TPersonagens));
	ListaPersonagens->QuantInimigos = Fase->QuantInimigos;
	ListaPersonagens->QuantRefens = 0;

	//Jogador
	ListaPersonagens->Jogador = PersonagemCriar();
	ListaPersonagens->Jogador->ID = JOGADORID;
	ListaPersonagens->Jogador->Altura = 32;
	ListaPersonagens->Jogador->ArquivoPele = CVetorCriar(MAX_VETORCHAR);
	strcpy(ListaPersonagens->Jogador->ArquivoPele, Fase->BitmapPeleJogador);
	ListaPersonagens->Jogador->EstaVivo = TRUE;
	ListaPersonagens->Jogador->Largura = 32;
	ListaPersonagens->Jogador->Nome = NULL;
	PersonagemPosicionar(ListaPersonagens->Jogador, Fase->PosicaoInicial);
	
	//Inimigos
	ListaPersonagens->Inimigos = (TPersonagem*)malloc(ListaPersonagens->QuantInimigos*sizeof(TPersonagem));
	for (i = 0; i < ListaPersonagens->QuantInimigos; i++)
	{
		PosicaoPersonagem.x = Fase->PosInimigo[i]->x;
		PosicaoPersonagem.y = Fase->PosInimigo[i]->y;
		//ListaPersonagens->Inimigos[i] = PersonagemCriar();
	
		ListaPersonagens->Inimigos[i].ID = i;
		ListaPersonagens->Inimigos[i].Altura = 32;
		ListaPersonagens->Inimigos[i].ArquivoPele = CVetorCriar(MAX_VETORCHAR);
		ListaPersonagens->Inimigos[i].Ativo = FALSE;
		ListaPersonagens->Inimigos[i].DelayParaCaminhar = 0;
		ListaPersonagens->Inimigos[i].DelayParaProcurar = 0;
		ListaPersonagens->Inimigos[i].EstaVivo = TRUE;
		ListaPersonagens->Inimigos[i].Largura = 32;
		ListaPersonagens->Inimigos[i].MascaraID = -1;
		ListaPersonagens->Inimigos[i].Nome = NULL;
		ListaPersonagens->Inimigos[i].PosicaoPernas = 0;
		ListaPersonagens->Inimigos[i].RecargaProjetil = 0;
		ListaPersonagens->Inimigos[i].Saude = 3;
		ListaPersonagens->Inimigos[i].TempoRecarga = 0;
		ListaPersonagens->Inimigos[i].Trajetoria.Norma = 1.50;
		ListaPersonagens->Inimigos[i].Trajetoria.Angulo = 90;
		ListaPersonagens->Inimigos[i].Trajetoria.Sentido = 1;
		ListaPersonagens->Inimigos[i].Transparencia = 255;
		ListaPersonagens->Inimigos[i].TransparenciaCont = 6;
		strcpy(ListaPersonagens->Inimigos[i].ArquivoPele, Fase->BitmapPeleInimigo);
		PersonagemPosicionar(&ListaPersonagens->Inimigos[i], PosicaoPersonagem);
	}
	
	//Refens
	ListaPersonagens->Refens = NULL;
	
	//Chefao
	ListaPersonagens->Chefao = PersonagemCriar();
	ListaPersonagens->Chefao->ID = CHEFAOID;
	ListaPersonagens->Chefao->Altura = 32;
	ListaPersonagens->Chefao->ArquivoPele = CVetorCriar(MAX_VETORCHAR);
	strcpy(ListaPersonagens->Chefao->ArquivoPele, Fase->BitmapPeleChefao);
	ListaPersonagens->Chefao->EstaVivo = TRUE;
	ListaPersonagens->Chefao->Largura = 32;
	ListaPersonagens->Chefao->Nome = NULL;
	PersonagemPosicionar(ListaPersonagens->Chefao, Fase->PosicaoChefao);

	return ListaPersonagens;
}

void JogoPersonagensDestruir(TPersonagens** Personagens)
{
	if ((*Personagens)->Chefao != NULL)
		PersonagemDestruir(&(*Personagens)->Chefao);	
	if ((*Personagens)->Jogador != NULL)
			PersonagemDestruir(&(*Personagens)->Jogador);
	if ((*Personagens)->Inimigos != NULL)
	{
		free((*Personagens)->Inimigos);
	}
	if ((*Personagens)->Refens != NULL)
	{
		free((*Personagens)->Refens);
	}
	free(*Personagens);
	*Personagens = NULL;
}

void JogoPersonagensAtirar(TJogo* Jogo)
{
	int i;
	TPersonagem* PersonagemAtual;
	
	for (i = 0; i < Jogo->Personagens->QuantInimigos; i++)
	{
		PersonagemAtual = &Jogo->Personagens->Inimigos[i];
		if (PersonagemVisivel(PersonagemAtual, &Jogo->MapaAtual->PontoVisao))
			if (PersonagemAtual->Ativo == TRUE)
			{
				if (PersonagemAtual->RecargaProjetil >= PersonagemAtual->TempoRecarga)
					{
						JogadorAtirar(Jogo, PersonagemAtual);
						TocarSomTiro(Jogo->BufferAudio, 0);
					}
			}		
	}
	PersonagemAtual = Jogo->Personagens->Chefao;
	if (PersonagemVisivel(PersonagemAtual, &Jogo->MapaAtual->PontoVisao))
		if (PersonagemAtual->Ativo == TRUE)
		{
			if (PersonagemAtual->RecargaProjetil >= PersonagemAtual->TempoRecarga)
			{
				JogadorAtirar(Jogo, PersonagemAtual);
				TocarSomTiro(Jogo->BufferAudio, 0);
			}
		}
}

void JogoPersonagensRecarregarProjetil(TJogo* Jogo)
{
	int i;
	TPersonagem* PersonagemAtual;
	
	PersonagemAtual = Jogo->Personagens->Jogador;
	if (PersonagemAtual->Ativo)
		PersonagemRecarregarProjetil(PersonagemAtual);
	
	PersonagemAtual = Jogo->Personagens->Chefao;
	if (PersonagemAtual->Ativo)
		PersonagemRecarregarProjetil(PersonagemAtual);
	
	for (i = 0; i < Jogo->Personagens->QuantInimigos; i++)
	{
		PersonagemAtual = &Jogo->Personagens->Inimigos[i];
		if (PersonagemAtual->Ativo)
			PersonagemRecarregarProjetil(PersonagemAtual);
	}
}

int JogoPausa(TJogo* Jogo)
{
	char* Titulo = "PAUSA";
	char* Frase1 = "Pressione ENTER para retornar ao jogo.";
	char* Frase2 = "Pressione ESCER para sair do jogo.";
	int resultado_menu = TRUE;
	int tecla;
	ALLEGRO_COLOR corBranca = al_map_rgb(255, 255, 255);
	int Teclas[1] = {ALLEGRO_KEY_ENTER};

	ConfigMouseCursor(Jogo->BufferBitmaps->Cursores[CUR_PADRAO]);
	while (resultado_menu)
	{
		al_draw_text(Jogo->BufferFontes->Fontes[FONTE_JANELA], corBranca, 250, 250, 0, Titulo);

		al_draw_text(Jogo->BufferFontes->Fontes[FONTE_TEXTO], corBranca, 250, 360, 0, Frase1);
		al_draw_text(Jogo->BufferFontes->Fontes[FONTE_TEXTO], corBranca, 250, 380, 0, Frase2);	
		TelaAtualizar();
		tecla = AguardaTecla(Teclas, 1);
		if ((Application.ClosingAll == TRUE) || (tecla == 0))
		{
			resultado_menu = FALSE;
		}
	}

	ConfigMouseCursor(Jogo->BufferBitmaps->Cursores[CUR_ALVO]);
	return TRUE;
}

void JogoPerdeu(TJogo* Jogo)
{
	char* Titulo = "VOCE PERDEU!";
	char* Frase1 = "Pressione ENTER para voltar ao menu do jogo.";
	int resultado_menu = TRUE;
	int tecla;
	ALLEGRO_COLOR corBranca = al_map_rgb(255, 255, 255);
	int Teclas[1] = {ALLEGRO_KEY_ENTER};

	ConfigMouseCursor(Jogo->BufferBitmaps->Cursores[CUR_PADRAO]);
	PararMelodia(Jogo->BufferAudio);
	TocarSomUnicaVez(Jogo->BufferAudio->Eventos[MELODIA_PERDER]);
	while (resultado_menu)
	{
		al_draw_text(Jogo->BufferFontes->Fontes[FONTE_JANELA], corBranca, 250, 250, 0, Titulo);
		al_draw_text(Jogo->BufferFontes->Fontes[FONTE_TEXTO], corBranca, 250, 380, 0, Frase1);	
		TelaAtualizar();
		tecla = AguardaTecla(Teclas, 1);
		if ((Application.ClosingAll == TRUE) || (tecla == 0))
		{
			resultado_menu = FALSE;
		}
	}	
}

int JogoPrepararBuffers(TJogo* Jogo)
{
	TPonto* Focos;
	char** ListaArquivos;
	int i;
	
	Jogo->BufferAudio = AudioBufferCriar();
	if (Jogo->BufferAudio == NULL)
		return FALSE;
	Jogo->BufferBitmaps = BitmapBufferCriar();
	if (Jogo->BufferBitmaps == NULL)
		return FALSE;
	Jogo->BufferFontes = FonteBufferCriar(3);
	if (Jogo->BufferFontes == NULL)
		return FALSE;
	
	//Bitmaps do mapa
	BitmapBufferAdicMapa(Jogo->BufferBitmaps, Jogo->MapaAtual->QuantMascaras, Jogo->MapaAtual->Mascaras);
	MapaConstruir(Jogo->MapaAtual, Jogo->FaseAtual->PosicaoFinal, Jogo->BufferBitmaps);
	//Cursores de mouse
	ListaArquivos = CMatrizCriar(2, MAX_VETORCHAR);
	Focos = (TPonto*)malloc(sizeof(TPonto)*2);
	strcpy(ListaArquivos[CUR_PADRAO], Jogo->CursorMouse);
	Focos[CUR_PADRAO].x = 0;
	Focos[CUR_PADRAO].y = 0;
	strcpy(ListaArquivos[CUR_ALVO], Jogo->MapaAtual->CursorMouse);
	Focos[CUR_ALVO].x = Jogo->MapaAtual->CursorFoco->x;
	Focos[CUR_ALVO].y = Jogo->MapaAtual->CursorFoco->y;
	BitmapBufferAdicCursores(Jogo->BufferBitmaps, 2, ListaArquivos, Focos);
	free(ListaArquivos);
	free(Focos);
	//Audios das eventos
	ListaArquivos = CMatrizCriar(3, MAX_VETORCHAR);
	strcpy(ListaArquivos[MELODIA_VENCER], "venceu.ogg");
	strcpy(ListaArquivos[MELODIA_PERDER], "morreu.ogg");
	strcpy(ListaArquivos[MELODIA_COMECAR], "comecando.ogg");
	AudioBufferAdicEventos(Jogo->BufferAudio, 3, ListaArquivos);
	free(ListaArquivos);
	//Audios das passadas
	ListaArquivos = CMatrizCriar(Jogo->MapaAtual->QuantPassadas, MAX_VETORCHAR);
	for (i = 0; i < Jogo->MapaAtual->QuantPassadas; i++)
	{
		strcpy(ListaArquivos[i], Jogo->MapaAtual->AudiosPassadas[i]);
	}
	AudioBufferAdicPassada(Jogo->BufferAudio, Jogo->MapaAtual->QuantPassadas, ListaArquivos);
	free(ListaArquivos);
	//Audio das vozes
	ListaArquivos = CMatrizCriar(1, MAX_VETORCHAR);
	strcpy(ListaArquivos[0], "voz_ala.ogg");
	AudioBufferAdicVozes(Jogo->BufferAudio, 1, ListaArquivos);
	free(ListaArquivos);
	//Bitmaps do personagens
	ListaArquivos = CMatrizCriar(3, MAX_VETORCHAR);
	strcpy(ListaArquivos[0], Jogo->Personagens->Jogador->ArquivoPele);
	strcpy(ListaArquivos[1], Jogo->Personagens->Chefao->ArquivoPele);
	strcpy(ListaArquivos[2], Jogo->Personagens->Inimigos[0].ArquivoPele);
	BitmapBufferAdicPerson(Jogo->BufferBitmaps, 3, ListaArquivos);
	free(ListaArquivos);
	//Bitmaps das armas
	ListaArquivos = CMatrizCriar(1, MAX_VETORCHAR);
	strcpy(ListaArquivos[0], "arma1.bmp");
	BitmapBufferAdicArmas(Jogo->BufferBitmaps, 1, ListaArquivos);
	free(ListaArquivos);
	//Audio de morte
	ListaArquivos = CMatrizCriar(1, MAX_VETORCHAR);
	strcpy(ListaArquivos[0], "morrer1.wav");
	AudioBufferAdicMorte(Jogo->BufferAudio, 1, ListaArquivos);
	free(ListaArquivos);
	//Audio dos projetis
	ListaArquivos = CMatrizCriar(1, MAX_VETORCHAR);
	strcpy(ListaArquivos[0], "tiro1.wav");
	AudioBufferAdicTiros(Jogo->BufferAudio, 1, ListaArquivos);
	free(ListaArquivos);
	//Musica ambiente
	AudioBufferSetMusAmbiente(Jogo->BufferAudio, Jogo->FaseAtual->MusicaAmbiente);
	AudioBufferPreparar(Jogo->BufferAudio);	
	//Bitmaps das pernas dos personagens
	BitmapBufferAdicPernas(Jogo->BufferBitmaps);
	//Fontes
	FonteBufferAdic(Jogo->BufferFontes, "titulo.ttf", 100);
	FonteBufferAdic(Jogo->BufferFontes, "menu.ttf", 35);
	FonteBufferAdic(Jogo->BufferFontes, "texto.ttf", 14);
	return TRUE;
}

int JogoPrepararDetectorColisoes(TJogo* Jogo)
{
	Jogo->DetectorColisoes = ColisorCriar(Jogo->MaxParticulas);
	
	return (Jogo->DetectorColisoes != NULL);
}

int JogoPrepararVetores(TJogo* Jogo)
{
	int i;
	
	Jogo->Projetis = (TProjetil**)malloc(Jogo->MaxProjetis * sizeof(TProjetil*));
	for (i = 0; i < Jogo->MaxProjetis; i++)
	{
		Jogo->Projetis[i] = NULL;
	}
	return (Jogo->Projetis != NULL);
}

void JogoTelaReposicionar(TJogo* Jogo)
{
	const int LimiteHorizontal = 360;
	const int LimiteVertical = 180;
	TPonto PontoFora;
	TPonto PontoJanela;

	PontoJanela.x = Jogo->Personagens->Jogador->Posicao.PontoInicial.x - Jogo->MapaAtual->PontoVisao.x;
	PontoJanela.y = Jogo->Personagens->Jogador->Posicao.PontoInicial.y - Jogo->MapaAtual->PontoVisao.y;
	if (PontoJanela.x > Application.ScreenWidth - LimiteHorizontal)
		PontoFora.x = PontoJanela.x - Application.ScreenWidth + LimiteHorizontal;
	else if	(PontoJanela.x < LimiteHorizontal)
		PontoFora.x = (LimiteHorizontal - PontoJanela.x) * -1;
	else
		PontoFora.x = 0;
	if (PontoJanela.y > Application.ScreenHeight - LimiteVertical)
		PontoFora.y = PontoJanela.y - Application.ScreenHeight + LimiteVertical;
	else if	(PontoJanela.y < LimiteVertical)
		PontoFora.y = (LimiteVertical - PontoJanela.y) * -1;
	else
		PontoFora.y = 0;
	if ((PontoFora.x != 0) || (PontoFora.y != 0))
		MapaMovimentar(Jogo->MapaAtual, &PontoFora);	
}

void JogoVenceu(TJogo* Jogo)
{
	char* Titulo = "VOCE VENCEU!";
	char* Frase1 = "Pô....você é foda, hein!!.";
	char* Frase2 = "Pressione ENTER para avancar no jogo.";
	int resultado_menu = TRUE;
	int tecla;
	ALLEGRO_COLOR corBranca = al_map_rgb(255, 255, 255);
	int Teclas[1] = {ALLEGRO_KEY_ENTER};

	ConfigMouseCursor(Jogo->BufferBitmaps->Cursores[CUR_PADRAO]);
	PararMelodia(Jogo->BufferAudio);
	TocarSomUnicaVez(Jogo->BufferAudio->Eventos[MELODIA_VENCER]);
	while (resultado_menu)
	{
		al_draw_text(Jogo->BufferFontes->Fontes[FONTE_JANELA], corBranca, 250, 250, 0, Titulo);
		al_draw_text(Jogo->BufferFontes->Fontes[FONTE_TEXTO], corBranca, 250, 380, 0, Frase1);	
		al_draw_text(Jogo->BufferFontes->Fontes[FONTE_TEXTO], corBranca, 250, 400, 0, Frase2);	
		TelaAtualizar();
		tecla = AguardaTecla(Teclas, 1);
		if ((Application.ClosingAll == TRUE) || (tecla == 0))
		{
			resultado_menu = FALSE;
		}
	}	
}

void JogadorAtirar(TJogo* Jogo, TPersonagem* Jogador)
{
	int i=0;
	TProjetil* NovoProjetil;
	
	Jogador->RecargaProjetil = 0;
	while (Jogo->Projetis[i] != NULL)
		i++;
	if (i >= Jogo->MaxProjetis)
		return;
	Jogo->Projetis[i] = ProjetilCriar(Jogador->PontoFrontal);
	NovoProjetil = Jogo->Projetis[i];
	NovoProjetil->ID = i;
	NovoProjetil->AtiradorID = Jogador->MascaraID;
	NovoProjetil->EFuncional = TRUE;
	NovoProjetil->EstaVivo = TRUE;
	NovoProjetil->Trajetoria.Angulo = Jogador->Trajetoria.Angulo;
	NovoProjetil->Trajetoria.Sentido = Jogador->Trajetoria.Sentido;
	ProjetilPosicionar(NovoProjetil);
	Jogo->ProjetisCont++;
}

void ProjetisDesenhar(TJogo* Jogo)
{
	int i;
	for(i = 0; i < Jogo->MaxProjetis; i++)
	{
		if (Jogo->Projetis[i] != NULL)
			if (Jogo->Projetis[i]->EstaVivo == TRUE)
			{
				ProjetilDesenhar(Jogo->Projetis[i], &Jogo->MapaAtual->PontoVisao);
			}
	}
}

void ProjetisMovimentar(TJogo* Jogo)
{
	int i;
	int MascID;
	TQuadra Posicao;
	TPersonagem* Atingido;
	
	for(i = 0; i < Jogo->MaxProjetis; i++)
	{
		if (Jogo->Projetis[i] != NULL)
		{
			if (Jogo->Projetis[i]->EstaVivo == TRUE)
			{
				ProjetilMovimentar(Jogo->Projetis[i]);
				if (Jogo->Projetis[i]->EFuncional == TRUE)
				{
					MascID = HaColisaoProjetil(Jogo->DetectorColisoes, Jogo->Projetis[i]->AtiradorID, &Jogo->Projetis[i]->PontoPartida, &Jogo->Projetis[i]->PontoDestino); 
					if (MascID >= 0)
					{
						Jogo->Projetis[i]->EFuncional = FALSE;
						Atingido = PersonagemPorMascara(Jogo->Personagens, MascID);
						if (Atingido != NULL)
						{
							PersonagemAtingir(Atingido);
							if (Atingido->Saude == 0)
							{
								PersonagemMatar(Atingido);
								ColisorMascaraRemover(Jogo->DetectorColisoes, MascID);
								TocarSomMorte(Jogo->BufferAudio, 0);
							}
						}
					}
					Posicao.PontoInicial.y = Jogo->Projetis[i]->PontoDestino.y;
					Posicao.PontoInicial.x = Jogo->Projetis[i]->PontoDestino.x;
					Posicao.PontoFinal.x = Jogo->Projetis[i]->PontoDestino.x + 2;
					Posicao.PontoFinal.y = Jogo->Projetis[i]->PontoDestino.y + 2;
					if (ChecarLimites(&Posicao, &Jogo->MapaAtual->PontoVisao))
					{ 
						Jogo->Projetis[i]->EFuncional = FALSE;
					}
				}
			}
			else if (Jogo->Projetis[i]->EstaVivo == FALSE)
			{
				free(Jogo->Projetis[i]);
				Jogo->Projetis[i] = NULL;
				Jogo->ProjetisCont--;
			}
		}
	}
}