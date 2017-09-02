#include <math.h>
#include <stdlib.h>
#include "matematica.h"
#include "fisica.h"

void PosicaoMovimentar(TPonto* Ponto, TVetor* Velocidade)
{
	float rad_angulo;

	rad_angulo = AnguloParaRadiano(Velocidade->Sentido * Velocidade->Angulo);
	Ponto->x = Ponto->x + Velocidade->Norma * cos(rad_angulo);
	Ponto->y = Ponto->y + Velocidade->Norma * sin(rad_angulo);
}