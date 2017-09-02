#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro.h>
#include "funcoes.h"
#include "vetor.h"
#include "arquivo.h"
#include "audio.h"
#include "graficos.h"
#include "fase.h"

TFase* FaseCriar(void)
{
	TFase* NovaFase;
	
	NovaFase = (TFase*)malloc(sizeof(TFase));
	NovaFase->ArquivoMapa = NULL;
	NovaFase->BitmapPeleChefao = NULL;	
	NovaFase->BitmapPeleJogador = NULL;
	NovaFase->BitmapPeleInimigo = NULL;	
	NovaFase->MusicaAmbiente = NULL;
	NovaFase->PosicaoChefao.x = 0;
	NovaFase->PosicaoChefao.y = 0;
	NovaFase->PosicaoInicial.x = 0;
	NovaFase->PosicaoInicial.y = 0;
	NovaFase->PosicaoFinal.x = 0;
	NovaFase->PosicaoFinal.y = 0;
	NovaFase->Prologo = NULL;
	NovaFase->QuantInimigos = 0;
	NovaFase->PosInimigo = NULL;
	
	return NovaFase;
}

void FaseDestruir(TFase** PFase)
{
	if ((*PFase)->ArquivoMapa != NULL)
		free((*PFase)->ArquivoMapa);
	if ((*PFase)->BitmapPeleChefao != NULL)
		free((*PFase)->BitmapPeleChefao);
	if ((*PFase)->BitmapPeleInimigo != NULL)
		free((*PFase)->BitmapPeleInimigo);
	if ((*PFase)->BitmapPeleJogador != NULL)
		free((*PFase)->BitmapPeleJogador);
	if ((*PFase)->MusicaAmbiente != NULL)
		free((*PFase)->MusicaAmbiente);	
	if ((*PFase)->Prologo != NULL)
		free((*PFase)->Prologo);
	if ((*PFase)->QuantInimigos > 0)
		MatrizDestruir((void***)&(*PFase)->PosInimigo, 1);
	free(*PFase);
	*PFase = NULL;	
}

int FaseAbrir(TFase* Fase, char* ArquivoFase)
{
	FILE* Arquivo;
	int TempInt;
	int i;
	
	Arquivo = ArquivoAbrir(REC_FASE, ArquivoFase);
	if (Arquivo != NULL)
	{
		if (!SecaoChecar(":ARQUIVOFASE", Arquivo))
		{
			fclose(Arquivo);
			return FALSE;
		}		

		if (LerPropriedadeInteiro("Versao", &TempInt, Arquivo))
		{
			if (TempInt != 1)
			{
				fclose(Arquivo);
				return FALSE;
			}
		}
		else
		{
			fclose(Arquivo);
			return FALSE;
		}

		if (!SecaoChecar(":DEFINICOES", Arquivo))
		{
			fclose(Arquivo);
			return FALSE;
		}
		Fase->Prologo = CVetorCriar(MAX_VETORCHAR);
		if (!Fase->Prologo)
		{
			fclose(Arquivo);
			return FALSE;
		}		
		if (!LerPropriedadeString("Prologo", Fase->Prologo, Arquivo))
		{
			fclose(Arquivo);
			return FALSE;
		}
		Fase->ArquivoMapa = CVetorCriar(MAX_VETORCHAR);
		if (!Fase->ArquivoMapa)
		{
			fclose(Arquivo);
			return FALSE;
		}		
		if (!LerPropriedadeString("ArquivoMapa", Fase->ArquivoMapa, Arquivo))
		{
			fclose(Arquivo);
			return FALSE;
		}		
		Fase->MusicaAmbiente = CVetorCriar(MAX_VETORCHAR);
		if (!Fase->MusicaAmbiente)
		{
			fclose(Arquivo);
			return FALSE;
		}		
		if (!LerPropriedadeString("MusicaAmbiente", Fase->MusicaAmbiente, Arquivo))
		{
			fclose(Arquivo);
			return FALSE;
		}
		if (!LerPropriedadePonto("PosJogadorInicial", &(Fase->PosicaoInicial), Arquivo))
		{	
			fclose(Arquivo);
			return FALSE;
		}
		if (!LerPropriedadePonto("PosJogadorFinal", &(Fase->PosicaoFinal), Arquivo))
		{
			fclose(Arquivo);
			return FALSE;
		}
		
		if (!SecaoChecar(":JOGADOR", Arquivo))
		{
			fclose(Arquivo);
			return FALSE;
		}		
		Fase->BitmapPeleJogador = CVetorCriar(MAX_VETORCHAR);
		if (Fase->BitmapPeleJogador == NULL)
		{
			fclose(Arquivo);
			return FALSE;
		}
		if (!LerPropriedadeString("ArquivoPele", Fase->BitmapPeleJogador, Arquivo))
		{
			fclose(Arquivo);
			return FALSE;
		}		

		if (!SecaoChecar(":CHEFAO", Arquivo))
		{
			fclose(Arquivo);
			return FALSE;
		}		
		Fase->BitmapPeleChefao = CVetorCriar(MAX_VETORCHAR);
		if (Fase->BitmapPeleChefao == NULL)
		{
			fclose(Arquivo);
			return FALSE;
		}
		if (!LerPropriedadeString("ArquivoPele", Fase->BitmapPeleChefao, Arquivo))
		{
			fclose(Arquivo);
			return FALSE;
		}
		if (!LerPropriedadePonto("PosChefao", &(Fase->PosicaoChefao), Arquivo))
		{	
			fclose(Arquivo);
			return FALSE;
		}

		if (!SecaoChecar(":INIMIGOS", Arquivo))
		{
			fclose(Arquivo);
			return FALSE;
		}		
		if (!LerPropriedadeInteiro("QuantInimigos", &Fase->QuantInimigos, Arquivo))
		{
			fclose(Arquivo);
			return FALSE;
		}
		Fase->PosInimigo = PMatrizCriar(Fase->QuantInimigos, 1);
		if (Fase->PosInimigo == NULL)
		{
			fclose(Arquivo);
			return FALSE;			
		}			
		Fase->BitmapPeleInimigo = CVetorCriar(MAX_VETORCHAR);
		if (Fase->BitmapPeleInimigo == NULL)
		{
			fclose(Arquivo);
			return FALSE;
		}
		if (!LerPropriedadeString("ArquivoPele", Fase->BitmapPeleInimigo, Arquivo))
		{
			fclose(Arquivo);
			return FALSE;
		}

		if (!SecaoChecar(":POSINIMIGOS", Arquivo))
		{
			fclose(Arquivo);
			return FALSE;
		}				
		for (i = 0; i < Fase->QuantInimigos; i++)
		{
			LerPropriedadePonto("PosInimigo", Fase->PosInimigo[i], Arquivo);
		}

		fclose(Arquivo);
		
		return TRUE;
	}
	else
		return FALSE;
}

void FaseIniciar(TFase* Fase)
{
	char* Caminho;
	TPonto PontoZero;
	ALLEGRO_BITMAP* BitmapAtual;
	
	//Exibir bitmap inicial da fase
	Caminho = ReceberRecDirCompleto(REC_IMAGEM, Fase->Prologo);
	BitmapAtual = al_load_bitmap(Caminho);
	free(Caminho);
	PontoZero.x = 0;
	PontoZero.y = 0;
	TelaDesenhar(BitmapAtual, &PontoZero);
	TelaAtualizar();
	al_destroy_bitmap(BitmapAtual);
}