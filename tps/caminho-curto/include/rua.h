#ifndef RUA_H
#define RUA_H

typedef struct TRua_ {
	int Origem;
	int Destino;
	int TempoMedio;
} TRua;


TRua* TRua_Criar(int Origem, int Destino, int TempoMedio);

void TRua_Destruir(void** PRua);
#endif