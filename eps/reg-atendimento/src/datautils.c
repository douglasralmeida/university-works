#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "datautils.h"

int HoraParaMinutos(THora Hora)
{
	return Hora;
}

void ImprimirHora(THora Hora)
{
	printf("%02d:%02d", Hora / 60, Hora % 60);
}

THora MinutosParaHora(int Minutos)
{
	return Minutos;
}

THora StringParaHora(char* Valor)
{
	char* s;
	THora Hora;

	s = strtok(Valor, ":");
	Hora = atoi(s) * 60;
	s = strtok(NULL, ":");
	Hora += atoi(s);
	
	return Hora;
}
