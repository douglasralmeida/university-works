#include <float.h>
#include <math.h>
#include <stdlib.h>
#include "matematica.h"

float AnguloParaRadiano(float Angulo)
{
	if (Angulo < -180)
		Angulo = Angulo + 360;
	if (Angulo > 180)
		Angulo = Angulo - 360;
	return -1 * Angulo / 180 * M_PI;
}

int ChecarLimites(TQuadra* Quadra, TPonto* PontoVisao)
{	
	if (Quadra->PontoInicial.x - PontoVisao->x < 0) 
		return TRUE;
	if (Quadra->PontoInicial.y - PontoVisao->y < 0)
		return TRUE;
	if (Quadra->PontoFinal.y - PontoVisao->y > TELA_ALTURA)
		return TRUE;
		//Quadra->PontoInicial.y = TELA_ALTURA - (Quadra->PontoFinal.y - Quadra->PontoInicial.y);
	if (Quadra->PontoFinal.x - PontoVisao->x > TELA_LARGURA)
		return TRUE;
	
	return FALSE;
		//Quadra->PontoInicial.x = TELA_LARGURA - (Quadra->PontoFinal.x - Quadra->PontoInicial.x);

//Alterar angulo do vetor velocidade ao chocar no limite horizontal:
//Objeto->Velocidade.Angulo = Objeto->Velocidade.Angulo + (180 - 2 * Objeto->Velocidade.Angulo);
//Altrar angulo do vetor velocidade ao chocar no limite vertical:
//Objeto->Velocidade.Sentido = Objeto->Velocidade.Sentido * -1;
}

float Determinante(float x1, float y1, float x2, float y2)
{
	return (x1 * y2 - x2 * y1);
}

float Max(float x1, float x2)
{
	if (x1 > x2)
		return x1;
	else
		return x2;
}

float Min(float x1, float x2)
{
	if (x1 < x2)
		return x1;
	else
		return x2;
}

int ExisteSobreposicaoQuadraPonto(TQuadra* Quadra, TPonto* Ponto)
{
	return ((Ponto->x > Quadra->PontoInicial.x) &&
			(Ponto->x < Quadra->PontoFinal.x) &&
			(Ponto->y > Quadra->PontoInicial.y) &&
			(Ponto->y < Quadra->PontoFinal.y));
}

int ExisteSobreposicaoQuadraReta(TQuadra* Quadra, TReta* Reta)
{
	int i = 0;
	int Resultado = FALSE;
	TReta RetaA;
	TPonto** Inters;
	
	Inters = (TPonto**)malloc(4 * sizeof(TPonto*));
	RetaA.Inicio.x = Quadra->PontoInicial.x;
	RetaA.Inicio.y = Quadra->PontoInicial.y;
	RetaA.Fim.x = Quadra->PontoFinal.x;
	RetaA.Fim.y = Quadra->PontoInicial.y;
	Inters[0] = RetasIntersecao(&RetaA, Reta);
	
	RetaA.Inicio.x = Quadra->PontoInicial.x;
	RetaA.Inicio.y = Quadra->PontoInicial.y;
	RetaA.Fim.x = Quadra->PontoInicial.x;
	RetaA.Fim.y = Quadra->PontoFinal.y;
	Inters[1] = RetasIntersecao(&RetaA, Reta);
	
	RetaA.Inicio.x = Quadra->PontoInicial.x;	
	RetaA.Inicio.y = Quadra->PontoFinal.y;
	RetaA.Fim.x = Quadra->PontoFinal.x;
	RetaA.Fim.y = Quadra->PontoFinal.y;	
	Inters[2] = RetasIntersecao(&RetaA, Reta);
	
	RetaA.Inicio.x = Quadra->PontoFinal.x;
	RetaA.Inicio.y = Quadra->PontoInicial.y;
	RetaA.Fim.x = Quadra->PontoFinal.x;
	RetaA.Fim.y = Quadra->PontoFinal.y;
	Inters[3] = RetasIntersecao(&RetaA, Reta);
	
	while ((Resultado == FALSE) && (i < 4))
	{
		Resultado = (Inters[i] != NULL);
		i++;		
	}
	for (i = 0; i < 4; i++)
		if (Inters[i] != NULL)
		{
			free(Inters[i]);
		}
	free(Inters);
	
	return Resultado;
}

int ExisteSobreposicaoQuadras(TQuadra* QuadraA, TQuadra* QuadraB)
{
    if ((QuadraA->PontoInicial.x > QuadraB->PontoFinal.x - 1) ||
        (QuadraA->PontoInicial.y > QuadraB->PontoFinal.y - 1) ||
        (QuadraB->PontoInicial.x > QuadraA->PontoFinal.x - 1) ||
        (QuadraB->PontoInicial.y > QuadraA->PontoFinal.y - 1))
    {
        return FALSE;
    }
    return TRUE;
}

int ExisteSobreposicaoRetas(TReta* RetaA, TReta* RetaB)
{
	int resultado;
	TPonto* Interseccao;
	
	Interseccao = RetasIntersecao(RetaA, RetaB);
	resultado = (Interseccao != NULL);
	free(Interseccao);
	return resultado;
}

float ObjetoPontoDistancia(TPonto* Ponto, TPonto* Objeto, unsigned int NumVertices)
{
	float Distancia;
	float MenorDistancia;
	unsigned int i;
	
	MenorDistancia = SegmentoPontoDistancia(Ponto, &Objeto[NumVertices-1], &Objeto[0]);
	for (i = 0; i < NumVertices - 1; i++)
	{
		Distancia = SegmentoPontoDistancia(Ponto, &Objeto[i], &Objeto[i+1]);
		if (Distancia < MenorDistancia)
			MenorDistancia = Distancia;
	}
	
	return MenorDistancia;
}

TPonto* PontoCriar(float x, float y)
{
	TPonto* NovoPonto;
	
	NovoPonto = (TPonto*)malloc(sizeof(TPonto));
	NovoPonto->x = x;
	NovoPonto->y = y;
	
	return NovoPonto;
}

void PontoRotacionar(TPonto* Ponto, TPonto* Centro, float Angulo)
{
	TPonto Temp;
	float rad_angulo;
	
	rad_angulo = AnguloParaRadiano(Angulo);
	
	Temp.x = Ponto->x - Centro->x;
	Temp.y = Ponto->y - Centro->x;
	Ponto->x = Temp.x * cos(rad_angulo) - Temp.x * sin(rad_angulo) + Centro->x;
	Ponto->y = Temp.x * sin(rad_angulo) - Temp.x * cos(rad_angulo) + Centro->y;
}

float PontosDistancia(TPonto* PontoA, TPonto* PontoB)
{
	return sqrt(powf(PontoB->x - PontoA->x, 2) + powf(PontoB->y - PontoA->y, 2));
}

float RadianoParaAngulo(float Rad_Angulo)
{
	return -1 * Rad_Angulo / M_PI * 180;
}

TPonto* RetasIntersecao(TReta* RetaA, TReta* RetaB)
{
	float tolerancia = 0.01;

	float a = Determinante(RetaA->Inicio.x - RetaA->Fim.x, RetaA->Inicio.y - RetaA->Fim.y, RetaB->Inicio.x - RetaB->Fim.x, RetaB->Inicio.y - RetaB->Fim.y);
	if (fabs(a) < FLT_EPSILON) 
		return NULL;

	float d1 = Determinante(RetaA->Inicio.x, RetaA->Inicio.y, RetaA->Fim.x, RetaA->Fim.y);
	float d2 = Determinante(RetaB->Inicio.x, RetaB->Inicio.y, RetaB->Fim.x, RetaB->Fim.y);
	float x = Determinante(d1, RetaA->Inicio.x - RetaA->Fim.x, d2, RetaB->Inicio.x - RetaB->Fim.x) / a;
	float y = Determinante(d1, RetaA->Inicio.y - RetaA->Fim.y, d2, RetaB->Inicio.y - RetaB->Fim.y) / a;

	if (x < Min(RetaA->Inicio.x, RetaA->Fim.x) - tolerancia || x > Max(RetaA->Inicio.x, RetaA->Fim.x) + tolerancia)
		return NULL;
	if (y < Min(RetaA->Inicio.y, RetaA->Fim.y) - tolerancia || y > Max(RetaA->Inicio.y, RetaA->Fim.y) + tolerancia)
		return NULL;
	if (x < Min(RetaB->Inicio.x, RetaB->Fim.x) - tolerancia || x > Max(RetaB->Inicio.x, RetaB->Fim.x) + tolerancia)
		return NULL;
	if (y < Min(RetaB->Inicio.y, RetaB->Fim.y) - tolerancia || y > Max(RetaB->Inicio.y, RetaB->Fim.y) + tolerancia)
		return NULL;

	return PontoCriar(x, y);
}

float RetaPontoDistancia(TReta* Reta, TPonto* Ponto)
{
	float a = Reta->Inicio.y - Reta->Fim.y;
	float b = Reta->Fim.x - Reta->Inicio.x;
	float c = Reta->Inicio.x * Reta->Fim.y - Reta->Fim.x * Reta->Inicio.y;
	
	return fabs(a * Ponto->x + b * Ponto->y + c) / sqrt(powf(a, 2) + powf(b, 2));
}

float SegmentoAngulo(TPonto* PontoInicial, TPonto* PontoFinal)
{
	return atan2(PontoFinal->y - PontoInicial->y, PontoFinal->x - PontoFinal->x);
}

float SegmentoPontoDistancia(TPonto* PontoInicial, TPonto* PontoFinal, TPonto* PontoA)
{
	float dist1;
	float dist2;
	float Angulo = SegmentoAngulo(PontoInicial, PontoFinal);
	float z = PontoA->x * cos(-1 * Angulo) + PontoA->y * sin(-1 * Angulo);
	float zi = PontoInicial->x * cos(-1 * Angulo) + PontoInicial->y * sin(-1 * Angulo);
	float zf = PontoFinal->x * cos(-1 * Angulo) + PontoFinal->y * sin(-1 * Angulo);
	TReta Reta;
	
	if ((zi < z && z < zf) || (zf < z && z < zi))
	{
		Reta.Inicio.x = PontoInicial->x;
		Reta.Inicio.y =PontoInicial->y;
		Reta.Fim.x = PontoFinal->x;
		Reta.Fim.y = PontoFinal->y;
		return RetaPontoDistancia(&Reta, PontoA);
	}
	else
	{
		dist1 = PontosDistancia(PontoA, PontoInicial);
		dist2 = PontosDistancia(PontoA, PontoFinal);
		if (dist1 < dist2)
			return dist1;
		else
			return dist2;
	}
}

void VetorInverter(TVetor* Vetor)
{
	Vetor->Angulo = 180 - Vetor->Angulo;
	Vetor->Sentido = -1 * Vetor->Sentido;
}

void VetorGirar90AH(TVetor* Vetor)
{
	if (Vetor->Sentido == 1)
	{
		Vetor->Angulo = Vetor->Angulo + 90;
		if (Vetor->Angulo > 180)
		{
				Vetor->Angulo = 360 - Vetor->Angulo;
			Vetor->Sentido = -1;
		}
	}
	else if (Vetor->Sentido == -1)
	{
		Vetor->Angulo = Vetor->Angulo - 90;
		if (Vetor->Angulo < 0)
		{
			Vetor->Angulo = -1 * Vetor->Angulo;
			Vetor->Sentido = 1;
		}
	}
}

void VetorGirar90H(TVetor* Vetor)
{
	if (Vetor->Sentido == 1)
	{
		Vetor->Angulo = Vetor->Angulo - 90;
		if (Vetor->Angulo < 0)
		{
			Vetor->Angulo = -1 * Vetor->Angulo;
			Vetor->Sentido = -1;
		}
	}
	else if (Vetor->Sentido == -1)
	{
		Vetor->Angulo = Vetor->Angulo + 90;
		if (Vetor->Angulo > 180)
		{
			Vetor->Angulo = -360 - Vetor->Angulo;
			Vetor->Sentido = 1;
		}
	}
}

TVetor* VetorDoisPontos(TPonto* PontoA, TPonto* PontoB)
{
	TVetor* NovoVetor;
	
	NovoVetor = (TVetor*)malloc(sizeof(TVetor));
	NovoVetor->Norma = PontosDistancia(PontoA, PontoB);
	NovoVetor->Angulo = RadianoParaAngulo(SegmentoAngulo(PontoA, PontoB));
	if (NovoVetor->Angulo < 0)
	{
		NovoVetor->Angulo = 180 - NovoVetor->Angulo;
		NovoVetor->Sentido = -1;
	}
	else
		NovoVetor->Sentido = 1;
	
	return NovoVetor;
}