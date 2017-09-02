#include <allegro5/allegro.h>
#include "vetor.h"
#include "funcoes.h"
#include "teclado.h"

int AguardaTecla(int* TeclasPossiveis, int n)
{
	ALLEGRO_EVENT_QUEUE *fila_eventos;
	int sai_loop = 0;
	int result = -1;
	
	fila_eventos = al_create_event_queue();
	al_register_event_source(fila_eventos, al_get_keyboard_event_source());
	al_register_event_source(fila_eventos, al_get_display_event_source(Application.Screen));

	while(!sai_loop)
	{
		ALLEGRO_EVENT evento;
		al_wait_for_event(fila_eventos, &evento);
		if (evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE) 
		{
			if (Pergunta(L"Voc\x00ea tem certeza que deseja encerrar o jogo?", 
							L"Sim, encerrar o jogo", 
							L"N\u00e3o, continuar no jogo"
						))
			{
				
				result = FECHAR_JANELA;
				sai_loop = 1;
				Application.ClosingAll = TRUE;
			}
		}
		else if (evento.type == ALLEGRO_EVENT_KEY_DOWN) 
		{
			result = IVetorPos(TeclasPossiveis, n, evento.keyboard.keycode);
			sai_loop = (result >= 0);
		}
	}
	al_destroy_event_queue(fila_eventos);
	return result;
}