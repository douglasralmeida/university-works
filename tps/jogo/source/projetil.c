#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include "projetil.h"

TProjetil* ProjetilCriar(TPonto PosicaoInicial)
{
	TProjetil* NovoProjetil;
	
	NovoProjetil = (TProjetil*)malloc(sizeof(TProjetil));
	NovoProjetil->ID = -1;
	NovoProjetil->Comprimento = 0;
	NovoProjetil->EFuncional = FALSE;
	NovoProjetil->EstaVivo = FALSE;
	NovoProjetil->Inicio.x = PosicaoInicial.x;
	NovoProjetil->Inicio.y = PosicaoInicial.y;
	NovoProjetil->Modo = pmCrescendo;
	NovoProjetil->PontoPartida.x = PosicaoInicial.x;
	NovoProjetil->PontoPartida.y = PosicaoInicial.y;
	NovoProjetil->Trajetoria.Norma = 30.0;
	NovoProjetil->Trajetoria.Angulo = 0.0;
	NovoProjetil->Trajetoria.Sentido = 1;

	return NovoProjetil;
}

void ProjetilDestruir(TProjetil** PProjetil)
{
	free(*PProjetil);
	PProjetil = NULL;
}

void ProjetilDesenhar(TProjetil* Projetil, TPonto* PontoVisao)
{
	ALLEGRO_COLOR corAmarela = al_map_rgba(255, 255, 255, 96);
	ALLEGRO_STATE EstadoAllegro;
	TPonto PontoJanelaInicio;
	TPonto PontoJanelaFim;
	
	if (Projetil->Comprimento > 0)
	{
		al_store_state(&EstadoAllegro, ALLEGRO_STATE_BLENDER);
		al_set_blender(ALLEGRO_ADD, ALLEGRO_ALPHA, ALLEGRO_INVERSE_ALPHA);
		
		PontoJanelaInicio.x = Projetil->Inicio.x - PontoVisao->x;
		PontoJanelaInicio.y = Projetil->Inicio.y - PontoVisao->y;
		PontoJanelaFim.x = Projetil->Fim.x - PontoVisao->x;
		PontoJanelaFim.y = Projetil->Fim.y - PontoVisao->y;
		
		al_draw_line(PontoJanelaInicio.x, PontoJanelaInicio.y, PontoJanelaFim.x, PontoJanelaFim.y, corAmarela, 1);
		al_restore_state(&EstadoAllegro);
	}
}

int ProjetilMovimentar(TProjetil* Projetil)
{
	TVetor Velocidade;
	
	switch (Projetil->Modo)
	{
		case pmCrescendo:
			Projetil->Comprimento++;
			if (Projetil->Comprimento >= 20)
			{
				Projetil->Modo = pmEstavel;
			}
			if (Projetil->EFuncional == FALSE)
				Projetil->Modo = pmDiminuindo;	
		break;
		case pmDiminuindo:
			Projetil->Comprimento--;
			if (Projetil->Comprimento <= 0)
			{
				Projetil->Modo = pmEstavel;
			}
		break;
		case pmEstavel:
			if ((Projetil->EFuncional == FALSE) && (Projetil->Comprimento > 0))
				Projetil->Modo = pmDiminuindo;
		break;
	}
	Velocidade.Angulo = Projetil->Trajetoria.Angulo;
	Velocidade.Norma = Projetil->Trajetoria.Norma;
	Velocidade.Sentido = Projetil->Trajetoria.Sentido;
	if (Projetil->Modo != pmDiminuindo)
	{
		PosicaoMovimentar(&Projetil->PontoDestino, &Velocidade);
		Projetil->Fim.x = Projetil->PosAnterior.x;
		Projetil->Fim.y = Projetil->PosAnterior.y;
		Projetil->PosAnterior.x = Projetil->PontoDestino.x;
		Projetil->PosAnterior.y = Projetil->PontoDestino.y;
	}
	if ((Projetil->Modo != pmCrescendo) && (Projetil->Comprimento > 0))
		PosicaoMovimentar(&Projetil->Inicio, &Velocidade);
	if ((Projetil->Modo == pmEstavel) && (Projetil->Comprimento == 0))
		Projetil->EstaVivo = FALSE;

	return TRUE;	
}
	
void ProjetilPosicionar(TProjetil* Projetil)
{
	TVetor Velocidade;
	
	Velocidade.Angulo = Projetil->Trajetoria.Angulo;
	Velocidade.Norma = 5;
	Velocidade.Sentido = Projetil->Trajetoria.Sentido;
	PosicaoMovimentar(&Projetil->PontoPartida, &Velocidade);
	Projetil->PontoDestino.x = Projetil->PontoPartida.x;
	Projetil->PontoDestino.y = Projetil->PontoPartida.y;
	Projetil->Fim.x = Projetil->PontoPartida.x;
	Projetil->Fim.y = Projetil->PontoPartida.y;
	Projetil->PosAnterior.x = Projetil->PontoPartida.x;
	Projetil->PosAnterior.y = Projetil->PontoPartida.y;
}