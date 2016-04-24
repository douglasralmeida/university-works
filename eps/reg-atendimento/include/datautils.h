#ifndef DATAUTILS_H
#define DATAUTILS_H

typedef int THora;

int HoraParaMinutos(THora Hora);
void ImprimirHora(THora Hora);
THora MinutosParaHora(int Minutos);
THora StringParaHora(char* Valor);

#endif