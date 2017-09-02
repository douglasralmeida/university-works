#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <stdlib.h>
#include "colisoes.h"

int HaColisaoLimites(TMascara* Mascara, TPonto* PontoVisao)
{	
	unsigned int i;
	
	for (i = 0; i < Mascara->VerticesCont; i += 3)
	{
		if (Mascara->Vertices[i].x - PontoVisao->x < 0) 
			return TRUE;
		if (Mascara->Vertices[i].y - PontoVisao->y < 0)
			return TRUE;
		if (Mascara->Vertices[i].y - PontoVisao->y > TELA_ALTURA)
			return TRUE;
		if (Mascara->Vertices[i].x - PontoVisao->x > TELA_LARGURA)
			return TRUE;
	}
	return FALSE;

//Alterar angulo do vetor velocidade ao chocar no limite horizontal:
//Objeto->Velocidade.Angulo = Objeto->Velocidade.Angulo + (180 - 2 * Objeto->Velocidade.Angulo);
//Altrar angulo do vetor velocidade ao chocar no limite vertical:
//Objeto->Velocidade.Sentido = Objeto->Velocidade.Sentido * -1;
}

int HaColisaoObjetos(TColisor* Colisor, unsigned int MascaraID)
{
	unsigned int i;
	
	for (i = 0; i < Colisor->MascarasCont; i++)
		if (MascaraID != i)
			if (Colisor->Mascaras[i].VerticesCont > 2)
				if (PoligonosSobreposicao(&Colisor->Mascaras[MascaraID], &Colisor->Mascaras[i]))
					{
						return i;
					}
	return -1;
}

int HaColisaoProjetil(TColisor* Colisor, unsigned int AtiradorID, TPonto* Inicio, TPonto* Fim)
{
	unsigned int i;
	TQuadra Quadra;
	TReta Reta;
	
	for (i = 0; i < Colisor->MascarasCont; i++)
		if (i != AtiradorID)
			if (Colisor->Mascaras[i].VerticesCont > 2)
			{
				Quadra.PontoInicial.x = Colisor->Mascaras[i].Vertices[0].x;
				Quadra.PontoInicial.y = Colisor->Mascaras[i].Vertices[0].y;
				Quadra.PontoFinal.x = Colisor->Mascaras[i].Vertices[3].x;
				Quadra.PontoFinal.y =  Colisor->Mascaras[i].Vertices[3].y;
				Reta.Inicio.x = Inicio->x;
				Reta.Inicio.y = Inicio->y;
				Reta.Fim.x = Fim->x;
				Reta.Fim.y = Fim->y;
				if (ExisteSobreposicaoQuadraReta(&Quadra, &Reta))
					return i;
			}

	return -1;
}

void MascaraDefinir(TMascara* Mascara, int NumVertices)
{
	Mascara->Vertices = (TPonto*)malloc(NumVertices * sizeof(TPonto));
	Mascara->VerticesCont = NumVertices;
}

void MascaraLimpar(TMascara* Mascara)
{
	if (Mascara->Vertices != NULL)
	{
		free(Mascara->Vertices);
		Mascara->Vertices = NULL;
		Mascara->VerticesCont = 0;
	}
}

void MascarasDesenhar(TColisor* Colisor, TPonto* PontoVisao)
{
	unsigned int i;
	int j;
	ALLEGRO_COLOR corAmarela = al_map_rgba(255, 255, 255, 96);
	float InicioX;
	float InicioY;
	float FimX;
	float FimY;
	int Pontos[4][2] = {{0, 1}, {1, 3}, {3, 2}, {2,0}};

	for (i = 0; i < Colisor->MascarasCont; i++)
	{
		if (Colisor->Mascaras[i].VerticesCont > 1)
		{
			for (j = 0; j < 4; j++)
			{
				InicioX = Colisor->Mascaras[i].Vertices[Pontos[j][0]].x - PontoVisao->x;
				InicioY = Colisor->Mascaras[i].Vertices[Pontos[j][0]].y - PontoVisao->y;
				FimX = Colisor->Mascaras[i].Vertices[Pontos[j][1]].x - PontoVisao->x;
				FimY = Colisor->Mascaras[i].Vertices[Pontos[j][1]].y - PontoVisao->y;
				al_draw_line(InicioX, InicioY, FimX, FimY, corAmarela, 1);
			}
		}
	}
}


TColisor* ColisorCriar(int Capacidade)
{
	int i;
	TColisor* NovoColisor;
	
	NovoColisor = (TColisor*)malloc(sizeof(TColisor));
	if (NovoColisor == NULL)
		return NULL;
	NovoColisor->Mascaras = (TMascara*)malloc(Capacidade * sizeof(TMascara));
	if (NovoColisor->Mascaras == NULL)
	{
		free(NovoColisor);
		return NULL;
	}
	for (i = 0; i < Capacidade; i++)
	{
		NovoColisor->Mascaras[i].Vertices = NULL;
		NovoColisor->Mascaras[i].VerticesCont = 0;
	}
	NovoColisor->MascarasCont = Capacidade;
	NovoColisor->MascaraProxPos = 0;
	
	return NovoColisor;
}

void ColisorDestruir(TColisor** PColisor)
{
	unsigned int i;
	
	for (i = 0; i < (*PColisor)->MascarasCont; i++)
	{
		MascaraLimpar(&(*PColisor)->Mascaras[i]);
	}
	free((*PColisor)->Mascaras);
	free(*PColisor);
	*PColisor = NULL;
}

int ColisorMascaraAdic(TColisor* Colisor, int NumVertices)
{
	if (Colisor->MascaraProxPos < Colisor->MascarasCont)
	{
		MascaraDefinir(&Colisor->Mascaras[Colisor->MascaraProxPos], NumVertices);
		Colisor->MascaraProxPos++;
		
		return Colisor->MascaraProxPos - 1;
	}
	else
	{
		return -1;
	}
}

void ColisorMascaraRemover(TColisor* Colisor, int MascaraID)
{
	MascaraLimpar(&Colisor->Mascaras[MascaraID]);
}

//Atualmente funciona apenas para paralelogramos...
int PoligonosSobreposicao(TMascara* MascaraA, TMascara* MascaraB)
{
    if ((MascaraA->Vertices[0].x > MascaraB->Vertices[3].x - 1) ||
        (MascaraA->Vertices[0].y > MascaraB->Vertices[3].y - 1) ||
        (MascaraB->Vertices[0].x > MascaraA->Vertices[3].x - 1) ||
        (MascaraB->Vertices[0].y > MascaraA->Vertices[3].y - 1))
    {
        return FALSE;
    }
    return TRUE;
}